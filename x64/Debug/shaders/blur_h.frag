uniform sampler2D texture;

uniform float weight[5] = float[] (0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);

void main()
{
	
	vec3 color = texture2D(texture, gl_TexCoord[0].xy).rgb + texture2D(texture, vec2(gl_TexCoord[0].x, gl_TexCoord[0].y)).rgb;
	/*float spread = 1;

	float tex_offset = 1.0 / textureSize(texture, 0).x;

	vec2 texelSize = (1.0/textureSize(texture, 0).x, 1.0/textureSize(texture, 0).y);
	vec2 texelOffset = vec2(texelSize.x, 0.0);
	
	vec3 color = vec3(0.0);
	
	float blurAmount = 3;

	for(int i = 1; i < spread*7; ++i)
    {
		//pixel3 += texture2D(texture, gl_TexCoord[0].xy + vec2(tex_offset * i, 0.0)).rgb * (1/(1+(i*i)/(spread)));
        //pixel3 += texture2D(texture, gl_TexCoord[0].xy - vec2(tex_offset * i, 0.0)).rgb * (1/(1+(i*i)/(spread)));

		color += texture2D(texture, gl_TexCoord[0].xy + texelOffset * (float(i) - blurAmount)).rgb * weight[i];
        color += texture2D(texture, gl_TexCoord[0].xy - texelOffset * (float(i) - blurAmount)).rgb * weight[i];
	}*/
    gl_FragColor = vec4(color, 1);
}