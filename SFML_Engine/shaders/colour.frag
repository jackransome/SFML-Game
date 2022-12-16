uniform sampler2D texture;
uniform vec4 colour;
void main()
{
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    if (pixel.r + pixel.g + pixel.b + pixel.a > 0){
        gl_FragColor = colour;
    }
    else{
        gl_FragColor = pixel;
    }
    gl_FragColor.a = 100;
    
    /*if (colour.a < 20){
        gl_FragColor = gl_Color vec4(255,0,255,100);
    }*/
}