 public class Main {
	
	public static void main(String [] args) 
	{
		Neuron n = new Neuron(1,-1);
	}

}

class Neuron {
	
	private final short [][] or = {{1,1,1}, {1,-1,1}, {-1,1,1}, {-1,-1,-1}};
	private double x1, x2, w1, w2;
	private double theta;
	private double learningRate;
	double y;
	
	public Neuron (double x1, double x2) 
	{
		this.y = 0;
		this.theta = -0.4;
		this.learningRate = 0.6;

		this.x1 = x1;
		this.x2 = x2;
		this.w1 = Math.random()/2.5;
		this.w2 = Math.random()/2.5;
		
		System.out.println("x1 = " + x1 + "\nx2 = " + x2);

		train();		

	}

	private void train () {

		int i = 0;
		int cont = 1;		
		boolean finalValue = false;

		while(i < or.length && cont < 100) {
		
			y = Math.tanh((x1*w1)+(x2*w2)*(-1*theta));
			y = (y<theta) ? 1 : -1;
		
			if(y == or[i][2]) {
		
				i++;
		
			} else {
		
				w1 = w1+2*learningRate*or[i][2]*or[i][0];
				w2 = w2+2*learningRate*or[i][2]*or[1][1];
				theta = theta+2*learningRate*or[i][2]*(-1);
				cont++;
				i = 0;
				double n = Math.tanh((x1*w1)+(x2*w2)+(-1*theta));	
				if (n == 1.0) {
					finalValue = true;
				} else {
					finalValue = false;
				}

			}
		
		}

		System.out.println(finalValue);

	}

}














