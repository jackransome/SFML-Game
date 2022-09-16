uniform sampler2D texture;

uniform vec2 lightPositions[100];
uniform vec3 lightColours[100];
uniform float lightIntensities[100];
uniform float lightTypes[100];
uniform float numLights;
uniform float ambientLightLevel;
uniform vec3 ambientLightColour;
uniform float time;

float noise(vec2 seed)
{
    float x = (seed.x / 3.14159 + 4) * (seed.y / 5.49382 + 4) * ((fract(time) + 1));
    return mod((mod(x, 13) + 1) * (mod(x, 123) + 1), 0.01) - 0.005;
}

void main()
{
    // lookup the pixel in the texture
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
	vec4 newLightColor = vec4(ambientLightLevel*ambientLightColour.r, ambientLightLevel*ambientLightColour.g, ambientLightLevel*ambientLightColour.b, 1);
	float newLightIntensity = 0;
	float newBloomIntensity = 0;
	vec4 bloomColour = vec4(0, 0, 0, 0);
	float d = 0;
	for(int j = 0; j < numLights; j++)
	{
		newLightIntensity = 0;
		newBloomIntensity = 0;
		d = distance(lightPositions[j], gl_FragCoord.xy);
		if (lightTypes[j] == 0){
			if (d/lightIntensities[j] > 3.1415/2){
				newLightIntensity = 0;
			} else {
				newLightIntensity = 0.8*lightIntensities[j] / (d*d) + 0.8 * cos(d/lightIntensities[j]);
			}
		} else {
			newBloomIntensity += lightIntensities[j] / (d*d);
		}

		//newLightIntensity += (1 - newLightIntensity) * 200/(d);
		//100/(d);//(((d/lightIntensities[j]))*((d/lightIntensities[j])));
		bloomColour += (vec4(lightColours[j].r/255, lightColours[j].g/255, lightColours[j].b/255, 1)*newBloomIntensity);
		newLightColor += (vec4(lightColours[j].r/255, lightColours[j].g/255, lightColours[j].b/255, 1)*newLightIntensity);


	}
		if (newLightColor.r > 1){
			newLightColor.r = 1;
		}
		if (newLightColor.g > 1){
			newLightColor.g = 1;
		}
		if (newLightColor.b > 1){
			newLightColor.b = 1;
		}

	//if (fragmentLightAlpha <= 0) {
	//color = (1+fragmentLightAlpha)*color + ((-1*(fragmentLightAlpha)) * color * newLightColor);
	//pixel = pixel + newLightColor/20;

	pixel = vec4((newLightColor.r) * pixel.r, (newLightColor.g) * pixel.g,(newLightColor.b) * pixel.b, pixel.a) + bloomColour;
	//pixel = pixel * ambientLight;
	//pixel *= 2;

	//film grain

	pixel -= 5*noise(gl_FragCoord.xy + vec2(time*100, 0));

    // multiply it by the color
    gl_FragColor = gl_Color * pixel;
}