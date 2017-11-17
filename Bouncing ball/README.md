## Bouncing Ball

We are going to look at a small subset of physics, the elastic collision of a 2D ball with a wall
and with another ball.

### Features

- `update_velocity_wall` A Ball method. Takes the `xdim` and `ydim` of the box and returns a
`TwoD`, the change of velocity.
- `update_velocity_ball` A Ball method. When two balls are in contact, the new velocity of the ball.