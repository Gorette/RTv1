camera {
	pos(0,0,-20)
	rotation(0,0,0)
}

light {
	pos(-24, 0, 10)
}

object {
	type(sphere)
	pos(20, -23, 20)
	radius(9)
}

object {
	type(plane)
	pos(0, 35, 0)
	vector(0, 1, 0)
	color(0, 0, 0)
}

object {
	type(plane)
	pos(0, -23, 0)
	vector(0, 1, 0)
	color(0, 0, 0)
}

object {
	type(cone)
	pos(0,35,30)
	rotation(90,0)
	angle(4)
}
