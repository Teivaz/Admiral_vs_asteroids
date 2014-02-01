{
"VertexShader":"
	attribute vec2 a_position;

	void main()
	{
		gl_Position =  vec4(a_position, 1.0, 1.0);
	}
"
,
"FragmentShader":"
	precision mediump float;
	
	void main()
	{
		gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
	}
"
}