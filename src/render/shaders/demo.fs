#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
   if (0.95f < texture(texture2, TexCoord).r && 
       0.95f < texture(texture2, TexCoord).b &&
       0.95f < texture(texture2, TexCoord).g ){
      FragColor = texture(texture1, TexCoord);
   } else {
      FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.5);
   }
}