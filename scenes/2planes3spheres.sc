camera {
	pos(0, 0, -10)
	rotation(0, 0, 0)
}

object {
	type(sphere)
	pos(0, 0, 100)
	radius(10)
	color(246, 189, 209)
}

object {
	type(sphere)
	pos(30, -30, 100)
	radius(10)
	color(246, 228, 246)
}

object {
	type(sphere)
	pos(-30, 30, 100)
	radius(10)
	color(201, 137, 134)
}

object {
	type(plane)
	pos(-50, -50, 0)
	color(244, 244, 244)
	vector(1, 1, 0.2)
}

object {
	type(plane)
	pos(50, 50, 0)
	color(137, 87, 92)
	vector(1, 1, -0.2)
}

light {
	pos(-40, 8, 20)
}
