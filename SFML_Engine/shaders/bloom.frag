uniform sampler2D texture;
uniform bool horizontal;

void main() {
    vec2 resolution = vec2(1920,1080);
    vec2 texCoords = gl_TexCoord[0].xy;
    vec3 color = vec3(0.0);

    // Gaussian blur weights and offsets
    const int blurSize = 9;
    const float weights[blurSize] = float[](0.140283, 0.115131, 0.082756, 0.052767, 0.029832, 0.014804, 0.006520, 0.002574, 0.000914);


    for (int i = 0; i < blurSize; ++i) {
        float weight = weights[i];
        vec2 offset = (horizontal ? vec2(i, 0.0) : vec2(0.0, i)) / resolution;

        color += texture2D(texture, texCoords + offset).rgb * weight;
        if (i > 0) {
            color += texture2D(texture, texCoords - offset).rgb * weight;
        }
    }

    gl_FragColor = vec4(color*2, 1.0);
}