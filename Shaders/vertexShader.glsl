attribute highp vec3 posAttr;
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

            highp vec4 worldPos=matrixT*matrixR*matrixS*vec4(posAttr, 1.0);

            highp vec4 worldNorm= matrixT*matrixS*matrixR*vec4(normAttr,0.0);

            gl_Position=matrixP*matrixV*worldPos;

            l = + vec3 (10.0,0.0,0.5) - worldPos.xyz;
            n = (worldNorm.xyz);
}
