uniform sampler2D texture;

void main()
{
	vec4 pixel = vec4(1,1,1,1);
	if (mod(gl_FragCoord.x, 4) <= 3 || mod(gl_FragCoord.y, 4) <= 3){
		pixel *= 0.3;
	}

    // multiply it by the color
    gl_FragColor = gl_Color * pixel;
}