uniform sampler2D texture;

uniform vec2 pointLightPositions[120];
uniform vec3 pointLightColours[120];
uniform float pointLightIntensities[120];
uniform float pointLightTypes[120];
uniform float numPointLights;

uniform vec2 beamLightPositions1[100];
uniform vec2 beamLightPositions2[100];
uniform vec3 beamLightColours[100];
uniform float beamLightIntensities[100];
uniform float beamLightTypes[100];
uniform float numBeamLights;

uniform float ambientLightLevel;
uniform vec3 ambientLightColour;
uniform float time;
uniform float noiseIntensity;

float noise(vec2 seed)
{
	//float newx = seed.x - mod(seed.x, 2);
	//float newy = seed.y - mod(seed.y, 2);
    float a = (seed.x / 3.14159 + 4.0) * (seed.y / 5.49382 + 4.0) * ((fract(time) + 1.0));
	//float b = (newx / 3.14159 + 4.0) * (newy / 5.49382 + 4.0) * ((fract(time) + 1.0));
    return mod((mod(a, 13.0) + 1.0) * (mod(a, 123.0) + 1.0), 0.01) - 0.005;// + mod((mod(b, 13) + 1.0) * (mod(b, 123) + 1.0), 0.01) - 0.005;
}

float distanceToLineSegment(vec2 point, vec2 a, vec2 b) {
    // Vector from a to b
    vec2 ab = b - a;
    // Vector from a to point
    vec2 ap = point - a;
    // Calculate the projection of ap onto ab, using dot product
    float projection = dot(ap, ab) / dot(ab, ab);
    // Clamp projection between 0.0 and 1.0 to ensure it lies within the line segment
    projection = clamp(projection, 0.0, 1.0);
    // Find the closest point on the line segment
    vec2 closestPoint = a + projection * ab;
    // Return the distance between the point and the closest point on the line segment
    return distance(point, closestPoint);
}

void main()
{
    // lookup the pixel in the texture
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
	if (pixel.a > 0.0){
		vec4 newLightColor = vec4(ambientLightLevel*ambientLightColour.r/255.0, ambientLightLevel*ambientLightColour.g/255.0, ambientLightLevel*ambientLightColour.b/255.0, 1.0);
		float newLightIntensity = 0.0;
		float newBloomIntensity = 0.0;
		vec4 bloomColour = vec4(0.0, 0.0, 0.0, 0.0);
		float d = 0.0;
		for(int j = 0; j < numPointLights; j++)
		{
			newLightIntensity = 0;
			newBloomIntensity = 0;
			d = distance(pointLightPositions[j], gl_FragCoord.xy);
			if (pointLightTypes[j] == 0.0){
					newLightIntensity = pointLightIntensities[j] / (d*d*0.00005 + 1.0);
			} else if (pointLightTypes[j] == 1.0) {
				newBloomIntensity = pointLightIntensities[j] / (d*d);
			} else if (pointLightTypes[j] == 2.0) {
				newBloomIntensity = pointLightIntensities[j] / (d*d);
				newLightIntensity = (pointLightIntensities[j]/20.0) / (d*d*0.00005 + 1.0);
			}
			
			bloomColour += (vec4(pointLightColours[j].r/255.0, pointLightColours[j].g/255.0, pointLightColours[j].b/255.0, 1)*newBloomIntensity);
			newLightColor += (vec4(pointLightColours[j].r/255.0, pointLightColours[j].g/255.0, pointLightColours[j].b/255.0, 1)*newLightIntensity);
		}

		for(int j = 0; j < numBeamLights; j++)
		{
			newLightIntensity = 0.0;
			newBloomIntensity = 0.0;
			d = distanceToLineSegment(gl_FragCoord.xy, beamLightPositions1[j], beamLightPositions2[j]);
			if (beamLightTypes[j] <= 0.01){
				newLightIntensity = beamLightIntensities[j] / (d*d*0.00005 + 1.0);
			} else if (beamLightTypes[j] <= 1.0) {
				newBloomIntensity = beamLightIntensities[j] / (d*d);
			} else if (beamLightTypes[j] == 2.0){
				newLightIntensity = (beamLightIntensities[j]/20.0) / (d*d*0.00005 + 1.0) + beamLightIntensities[j] / (d*d);
				
				//newLightIntensity = max(0.0, (beamLightIntensities[j] - beamLightIntensities[j])/beamLightIntensities[j]);
				//newBloomIntensity = max(0.0, (beamLightIntensities[j] - beamLightIntensities[j])/beamLightIntensities[j]);
			}
			//newLightIntensity = max(0.0, (5 - d)/5);
			//newBloomIntensity = max(0.0, (5 - d)/5);
			bloomColour += (vec4(beamLightColours[j].r/255.0, beamLightColours[j].g/255.0, beamLightColours[j].b/255.0, 1.0)*newBloomIntensity);
			newLightColor += (vec4(beamLightColours[j].r/255.0, beamLightColours[j].g/255.0, beamLightColours[j].b/255.0, 1.0)*newLightIntensity);
			
			/*if (d < 10){
				newLightColor = vec4(0,1,0,1);
				bloomColour = vec4(0,1,0,1);
			}
			if (d < 3) {
				newLightColor += vec4(0,0,1,1);
			}*/
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

		pixel = vec4((newLightColor.r) * pixel.r, (newLightColor.g) * pixel.g,(newLightColor.b) * pixel.b, pixel.a) + bloomColour;

		//if (fragmentLightAlpha <= 0) {
		//color = (1+fragmentLightAlpha)*color + ((-1*(fragmentLightAlpha)) * color * newLightColor);
		//pixel = pixel + newLightColor/20;

	
		//pixel = pixel * ambientLight;
		//pixel *= 2;

		//film grain

		float t = pixel.a;
		pixel -= noiseIntensity*4*noise(gl_FragCoord.xy + vec2(time*100, 0));
		pixel.a = t;
	}



    // multiply it by the color
    gl_FragColor = gl_Color * pixel;
}