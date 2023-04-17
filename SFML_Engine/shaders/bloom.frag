uniform sampler2D texture;
uniform bool horizontal;

void main() {
    vec2 resolution = vec2(1920,1080);
    vec2 texCoords = gl_TexCoord[0].xy;

    // Gaussian blur weights and offsets
    const int blurSize = 15;

    // Recalculate Gaussian blur weights for 15 pixels radius
    const float weights[blurSize] = float[](
        0.10650697891920052, 0.09132463527510419, 0.07136786967797782,
        0.050042588506527204, 0.03144854070679338, 0.017906466768683014,
        0.009233426144012373, 0.004329255996812929, 0.0018473625145993554,
        0.0007213643851362284, 0.0002549397928465474, 0.00008036896619445638,
        0.000023453032718264536, 0.000006162950107066107, 0.000001448476242467264
    );

    bool horizontal = true;
    float threshold = 0.0;
    vec3 color = texture2D(texture, texCoords).rgb * weights[0];
    vec3 temp;
    for (int i = 0; i < blurSize; ++i) {
        float weight = weights[i];
        vec2 offset = (horizontal ? vec2(i, 0.0) : vec2(0.0, i)) / resolution;

        if (i > 0) {
            temp = texture2D(texture, texCoords + offset).rgb;
            color += temp * weight;
            temp = texture2D(texture, texCoords - offset).rgb;
            color += temp * weight;
        }
    }

    gl_FragColor = vec4(color*1.5, 1);
}