
attribute vec4 gl_Vertex;

void main()
{
  // gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
  // gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
  gl_Position = ftransform();
}