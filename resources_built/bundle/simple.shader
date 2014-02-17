{
"VertexShader":"
	attribute vec2 a_position;
	attribute vec2 a_texturePosition;

	uniform mat3 u_transformation;
	uniform sampler2D u_texture;

	varying vec2 v_texturePosition;
	
	void main()
	{
		v_texturePosition = a_texturePosition;
		vec3 pos = vec3(a_position, 1.0) * u_transformation;
	#ifdef IOS
		gl_Position =  vec4(-pos.y, pos.x, 0.0, 1.0);
	#else
		gl_Position =  vec4(pos.x, pos.y, 0.0, 1.0);
	#endif
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