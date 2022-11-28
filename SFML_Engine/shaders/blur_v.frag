uniform sampler2D texture;

uniform float weight[5] = float[] (0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);

void main()
{
	vec3 pixel3 = texture2D(texture, gl_TexCoord[0].xy).rgb;
	float spread = 1;
	float tex_offset = 1.0 / textureSize(texture, 0).y;
	for(int i = 1; i < spread*7; ++i)
    {
		pixel3 += texture2D(texture, gl_TexCoord[0].xy + vec2(0.0, tex_offset * i)).rgb * (1/(1+(i*i)/(spread)));
        pixel3 += texture2D(texture, gl_TexCoord[0].xy - vec2(0.0, tex_offset * i)).rgb * (1/(1+(i*i)/(spread)));
	}
    gl_FragColor = vec4(pixel3, 1);
}