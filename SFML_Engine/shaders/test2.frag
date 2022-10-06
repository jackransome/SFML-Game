uniform sampler2D texture;

void main()
{
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy+ vec2(0,0));
	//18*38
	pixel += texture2D(texture, gl_TexCoord[0].xy + vec2(1.0/18.0,0))*0.2;
	pixel += texture2D(texture, gl_TexCoord[0].xy + vec2(-1.0/18.0,0))*0.2;
	pixel += texture2D(texture, gl_TexCoord[0].xy + vec2(0,1.0/38.0))*0.2;
	pixel += texture2D(texture, gl_TexCoord[0].xy + vec2(0,-1.0/38.0))*0.2;
	
    // multiply it by the color
    gl_FragColor = gl_Color * pixel;
}