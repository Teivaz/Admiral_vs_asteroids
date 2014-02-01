{
"VertexShader":"
	attribute vec2 a_position;
	attribute vec2 a_texturePosition;

	uniform sampler2D u_texture;

	varying vec2 v_texturePosition;
	
	void main()
	{
		v_texturePosition = vec2(a_texturePosition.x, 1.0 - a_texturePosition.y);
		gl_Position =  vec4(a_position, 1.0, 1.0);
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