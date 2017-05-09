varying highp vec3 n;
varying highp vec3 l;
uniform highp vec4 col;
        void main() {
                highp vec4 diffColor = col;
                highp float factor    = 0.5;
                highp vec3 n2   = normalize ( n );
                highp vec3 l2   = normalize ( l );
                highp vec4 diff = diffColor * max ( dot ( n2, l2 ) + factor, 0.5 )/(1.0+factor);
                gl_FragColor = diff;

}
