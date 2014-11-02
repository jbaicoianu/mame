precision highp float;

attribute vec2 position;
attribute vec2 uv;

uniform mat4 viewMatrix;
uniform vec2 offset;
uniform vec2 size;

varying vec2 vUv;

void main()
{
  vUv = uv;
  vec2 pos2d = offset + (position * size);
  gl_Position = vec4(pos2d.x, pos2d.y, 0, 1);
}

