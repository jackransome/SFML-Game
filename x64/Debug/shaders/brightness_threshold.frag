uniform sampler2D texture;

void main() {
    /*float threshold = 0.8;
    vec2 texCoords = gl_TexCoord[0].xy;
    vec4 color = texture2D(texture, texCoords).rgba;

    float brightness = max(color.r, max(color.g, color.b));
    vec4 filteredColor = brightness > threshold ? color : vec4(0.0);

    gl_FragColor = filteredColor;*/
    vec2 texCoords = gl_TexCoord[0].xy;
    vec4 color = texture2D(texture, texCoords).rgba;
    float brightness = dot(color.rgb, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 0.9){
        gl_FragColor = vec4(color.rgb * brightness * brightness, 1.0);
        gl_FragColor = vec4(color.rgb, 1.0);
    }
    else {
    gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    }
        
    
}