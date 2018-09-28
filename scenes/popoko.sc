camera {
	pos(0,0,-20)
	rotation(0,0,0)
}

light {
	pos(-21, 0, 29)
}

object {
	type(sphere)
	pos(-10, -15, 30)
	radius(7)
	color(254,195,172)
}

object {
	type(sphere)
	pos(20, -23, 20)
	radius(9)
	color(254,195,172)
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
	color(254,195,172)
}
