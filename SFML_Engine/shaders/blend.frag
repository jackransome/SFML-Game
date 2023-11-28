uniform sampler2D texture;
uniform sampler2D texture2;

/*void main()
{          
    vec2 texCoords = gl_TexCoord[0].xy;
    float exposure = 1;
    const float gamma = 1;
    vec3 hdrColor = texture2D(texture, texCoords).rgb;      
    vec3 bloomColor = texture2D(texture2, texCoords).rgb;
    hdrColor += bloomColor; // additive blending
    // tone mapping
    vec3 result = vec3(1.0) - exp(-hdrColor * exposure);
    // also gamma correct while we're at it       
    result = pow(result, vec3(1.0 / gamma));
    gl_FragColor = vec4(result, 1.0);
    gl_FragColor = vec4(texture2D(texture, texCoords).rgb + texture2D(texture2, texCoords).rgb, 1.0);
} */


void main()
{
    vec2 texCoords = gl_TexCoord[0].xy;

    // Sample colors from both textures
    vec4 color1 = texture2D(texture, texCoords);
    vec4 color2 = texture2D(texture2, texCoords);

    // Use the alpha channel of texture2 as the opacity for blending
    float opacity = color2.a;

    // Linear interpolation blending using the opacity
    vec3 blendedColor = mix(color1.rgb, color2.rgb, opacity);

    // Set the final color
    gl_FragColor = vec4(blendedColor, 1.0);
}
