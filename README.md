This is My Graphic Project.

I wanted to make easy use of shader program.

<b>How to build</b>
simply you need to run Make-Solution.bat in order to generate visual stuido solution file.
and build it you will see exe files inside of bin folder.

<b>control</b>
control with gui

<b>Simple tutorial of heapoverflow project</b>


Code:
```cpp
using namespace hof;
//set data to send gpu
std::shared_ptr<VertexBuffer> vertexBuffer = std::make_shared<VertexBuffer>(vertices, (unsigned int)sizeof(vertices));
//easy way to describe data to be used by gpu 
vertexBuffer->DescribeData({  
{DataType::Float3,0},  //let's assume we are sending vec3 position and vec4 color in one vertex buffer.
{DataType::Float4,1}   //{ data type, layout location in glsl}
});

//creation of making elementry buffer. 
unsigned int indices[3] = { 0,1,2 };
std::shared_ptr<IndexBuffer> indexBuffer = std::make_shared<IndexBuffer>(indices, 3);

//link it those buffers to vertex array object.
std::shared_ptr<VertexArray> VertexArray = std::make_shared<VertexArray>();

VertexArray->AddVertexBuffer(vertexBuffer);
VertexArray->AddIndexBuffer(indexBuffer);
//creation of shader program.
std::shared_ptr<Shader> ShaderProgram = std::make_shared<Shader>("resource/default.vert", "resource/default.frag");
//drawing.
Renderer::SetClearColor({ 0.2f,0.3f,0.5f,1.0f });
Renderer::ClearScreen();
ShaderProgram->Bind();
VertexArray->Bind();
Renderer::DrawIndexed(m_VertexArray);
```

