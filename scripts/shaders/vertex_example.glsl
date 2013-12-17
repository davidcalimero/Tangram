/// <summary>
/// Attributes.
/// <summary>
attribute vec3 Vertex;
attribute vec2 Uv;


/// <summary>
/// Uniform variables.
/// <summary>
uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;
uniform vec3 ModelScale;


/// <summary>
/// Varying variables.
/// <summary>
varying vec2 vUv;


/// <summary>
/// Vertex shader entry.
/// <summary>
void main ()
{
    vec4 worldVertex = ModelMatrix * vec4(Vertex * ModelScale, 1.0);
    vec4 viewVertex = ViewMatrix * worldVertex;
    gl_Position = ProjectionMatrix * viewVertex;
    
    vUv = Uv;
}