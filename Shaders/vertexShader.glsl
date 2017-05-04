attribute highp vec4 posAttr;
         uniform highp mat4 matrixP;
         uniform highp mat4 matrixT;
         uniform highp mat4 matrixR;
         uniform highp mat4 matrixS;
         uniform highp mat4 matrixV;
         varying highp vec3 curPos;

        void main() {
           gl_Position=matrixR*posAttr;


           gl_Position=matrixS*gl_Position;
           gl_Position=matrixT*gl_Position;

           curPos=gl_Position.xyz;
          gl_Position=matrixV*gl_Position;
           gl_Position=matrixP*gl_Position;

}
