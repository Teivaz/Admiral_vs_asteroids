{
"VertexShader":"
	attribute vec2 a_position;
	attribute vec2 a_texturePosition;

	uniform mat3 u_transformation;
	uniform sampler2D u_texture;

	varying vec2 v_texturePosition;
	
	void main()
	{
		v_texturePosition = vec2(a_texturePosition.x, 1.0 - a_texturePosition.y);
		vec3 pos = vec3(a_position, 1.0) * u_transformation;
		gl_Position =  vec4(pos, 1.0);
	}
"
,
"FragmentShader":"
	precision mediump float;
		
	uniform sampler2D u_texture;
	
	varying vec2 v_texturePosition;

	void main()
	{
		gl_FragColor = texture2D(u_texture, v_texturePosition);
	}
"
}