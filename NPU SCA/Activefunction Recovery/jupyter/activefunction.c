float Hardsigmoid(float h)
{
	return (h > 2.5 ? 1 : (h < -2.5 ? 0 : 0.2*h + 0.5));
}

float LeaklyReLU(float h)
{
	return (h > 0 ? h : 0.01*h);
}


float ELU(float h)
{
	return (h > 0 ? h : exp(h) - 1);
}


float Softplus(float h)
{
	return log(exp(h) + 1);
}


float Softsign(float h)
{
	return h / 1 + abs(h);
}

float Swish(float h)
{
	return (1 / (1 + exp(-h))) * h;
}


// Linear / Step
