uniform sampler2D texture;

void main()
{
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    gl_FragColor = pixel + vec4(0,0,1,0);
}