varying highp vec3 n;
varying highp vec3 l;
uniform highp vec4 col;
        void main() {
                highp vec4 diffColor = col;
                highp vec3 n2   = normalize ( n );
                highp vec3 l2   = normalize ( l );
                highp vec4 diff = diffColor * max ( dot ( n2, l2 ), 0.0 );
                gl_FragColor = diff;

}
