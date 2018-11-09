camera {
	pos(-1,-1,-1)
	rotation(-1,-1,-1)
}

object {
	shiny
	type(sphere)
	pos(-1,-1,10)
	radius(2)
	color(-255,-2,-2)
}

object {
	type(plane)
	pos(0,-1,200)
	vector(-10,-10,-10)
	color(125,149,238)
}

object {
	shiny
	type(cone)
	pos(5,0,30)
	angle(20)
	rotation(90,45)
	color(255,255,0)
}

light {
	pos(0,0,-100)
}
