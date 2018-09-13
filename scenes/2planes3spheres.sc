camera {
	pos(0, 0, 0)
	dir(0, 0, 1)
}

object {
	type(sphere)
	pos(0, 0, 100)
	radius(10)
}

object {
	type(sphere)
	pos(30, -30, 100)
	radius(10)
	color(246, 125, 210)
}

object {
	type(sphere)
	pos(-30, 30, 100)
	radius(10)
	color(153, 125, 246)
}

object {
	type(plane)
	pos(-50, -50, 0)
	color(171, 202, 238)
	vector(1, 1, 0.2)
}

object {
	type(plane)
	pos(50, 50, 0)
	color(135, 246, 125)
	vector(1, 1, -0.2)
}
