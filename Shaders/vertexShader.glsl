attribute highp vec4 posAttr;
attribute highp vec3 normAttr;
         uniform highp mat4 matrixP;
         uniform highp mat4 matrixT;
         uniform highp mat4 matrixR;
         uniform highp mat4 matrixS;
         uniform highp mat4 matrixV;
         varying highp vec3 curPos;
         varying highp vec3 n;
         varying highp vec3 l;

        void main() {
            gl_PointSize =2.0;

            gl_Position=matrixR*posAttr;
            gl_Position=matrixS*gl_Position;
            gl_Position=matrixT*gl_Position;

            highp vec4 worldNorm= matrixT*matrixS*matrixR*vec4(normAttr,1.0);

            highp vec4 worldPos = gl_Position;
            gl_Position=matrixV*gl_Position;
            gl_Position=matrixP*gl_Position;

            l = + vec3 (10.0,0.0,0.5) - worldPos.xyz;
            n = (worldNorm.xyz);

}
