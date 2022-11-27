uniform sampler2D texture;

void main()
{
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
	if ((mod(gl_FragCoord.x, 4) <= 3 || mod(gl_FragCoord.y, 4) <= 3)){
		pixel.r *= 0.3;
		pixel.g *= 0.3;
		pixel.b *= 0.3;
		pixel.a *= 0.3;
	}

    // multiply it by the color
    gl_FragColor = gl_Color * pixel;
}