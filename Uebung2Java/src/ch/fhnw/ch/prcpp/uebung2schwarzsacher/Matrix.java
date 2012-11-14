package ch.fhnw.ch.prcpp.uebung2schwarzsacher;

import java.util.Random;

public class Matrix {
	static {
		System.loadLibrary("Uebung2");
	}
	
	private int rows, cols;

	/**
	 * holds the matrix' data<br>
	 * the element at <b>row x</b> and <b>col y</b> is stored at
	 * <b>matrix[x*cols + y]</b>
	 */
	private double[] matrix;
	
	public Matrix(int height, int width) {
		createMatrix(height, width);
		
		Random dice = new Random(56874534184132L); // typed furiously, guaranteed to be random ;) --öh,was secher ned! :D
		for (int i=0; i<cols*rows; i++) {
			matrix[i] = dice.nextDouble();
		}
	}
	
	public Matrix(int height, int width, double value) {
		createMatrix(height, width);
		
		for (int i=0; i<cols*rows; i++) {
			matrix[i] = value;
		}
	}
	
	private Matrix(int height, int width, double[] data) {
		assert height>0 && width>0;
		this.rows = height;
		this.cols = width;
		matrix = data;
	}

	private void createMatrix(int height, int width) {
		assert height>0 && width>0;
		this.rows = height;
		this.cols = width;
		matrix = new double[height*width];
	}

	/**
	 * get an element
	 * @param position
	 * @return element at row position/getWidth() and col position%getWidth()
	 */
	public double getElement(int position) {
		assert position < rows*cols && position >= 0;
		return matrix[position];
	}
	
	private double[] getData() {
		return matrix;
	}
	
	/**
	 * get an element
	 * @param row self-explanatory
	 * @param col self-explanatory
	 * @return element at row row and col col
	 */
	public double getElement(int row, int col) {
		final int pos = row*cols + col;
		assert pos >= 0 && pos < rows*cols;
		return matrix[pos];
	}
	
	@Override
	public boolean equals(Object other) {
		Matrix otherMatrix = (Matrix) other;
		for (int i=0; i<cols*rows; i++) {
			if (matrix[i] != otherMatrix.getElement(i)) return false;
		}
		return true;
	}
	
	public int getWidth() {
		return cols;
	}

	public int getHeight() {
		return rows;
	}
	
	/**
	 * multiply with another matrix
	 * @param b the other matrix, this.getWidth() has to be equal to b.getHeight()
	 * @return returns the result of the multiplication this*b, with height this.getHeight()
	 * and width b.getWidth()
	 */
	public Matrix multiply(Matrix b) {
		assert rows == b.getWidth();
		double[] result = prepareMultiplication(rows, b.getWidth());
		final int rH = rows;
		final int rW = b.getWidth();
		
		for (int row=0; row<rH; row++) { // row in result
			for (int col=0; col<rW; col++) { // col in result
				for (int k=0; k<cols; k++) {
					result[row*rW + col] += matrix[row*cols + k] * b.getData()[k*rW + col];
				}
			}
		}
		
		return new Matrix(rows, b.getWidth(), result);
	}

	public Matrix power(int k) {
		Matrix result = new Matrix(rows,cols);
		
		switch (k) {
		case 0:
			// Einheitsmatrix retournieren?
			for (int i=0; i<rows; i++) {
				result.getData()[i*rows + i] = 1.0;
			}
			break;
		case 1:
			for (int i=0; i<rows*cols; i++) {
				result.getData()[i] = matrix[i];
			}
			break;
		default:
			// k>=2
			result = this.multiply(this);
			for (int i=2; i<k; i++) {
				// this always creates a new Matrix and array, performance...
				result = result.multiply(this);
			}
			break;
		}
		
		return result; 
	}

	public Matrix multiplyNative(Matrix b) {
		assert rows == b.getWidth();
		double[] result = prepareMultiplication(rows, b.getWidth());
		multiplyC(matrix, b.getData(), result, rows, cols, b.getWidth());
		return new Matrix(rows, b.getWidth(), result);
	}

	public Matrix powerNative(int k){
		double[] result = prepareMultiplication(rows, cols);
		powerC(matrix, result,k, rows, cols);
		return new Matrix(rows,cols,result);
	}
	
	public void print() {
		for (int row=0; row<rows; row++) {
			for (int col=0; col<cols; col++) {
				System.out.printf("%.1f\t", matrix[row*cols + col]);
			}
			System.out.print('\n');
		}
	}
	
	private double[] prepareMultiplication(int heightA, int widthB) {
		return new double[heightA*widthB];
	}
	
	private native void multiplyC(double[] matrixA, double[] matrixB, double[] result,
			int heightA, int widthA, int widthB);

	private native void powerC(double[] matrixA, double[] result,int k, int height, int width);

	public static void main(String[] args) {
		// example from http://de.wikipedia.org/wiki/Matrix_%28Mathematik%29#Matrizenmultiplikation
//		Matrix a = new Matrix(2, 3, new double[]{1,2,3,4,5,6});
//		Matrix b = new Matrix(3, 2, new double[]{6,-1,3,2,0,-3});
//		Matrix rJ = a.multiply(b);
//		Matrix rC = a.multiplyNative(b);
//		rJ.print();
//		System.out.println();
//		rC.print();
		
		Matrix c = new Matrix(400, 6000);
		Matrix d = new Matrix(6000, 300);
		Matrix p = new Matrix(200,200);
	
			
		System.out.println("matrix multiplication: ");
		long startJ = System.currentTimeMillis();
		Matrix rJ = c.multiply(d);
		System.out.println("java took " + (System.currentTimeMillis()-startJ) + "ms");
		
	//	long startC = System.currentTimeMillis();
		Matrix rC = c.multiplyNative(d);
	//	System.out.println("c++ took " + (System.currentTimeMillis()-startC) + "ms");


		System.out.println("matrix power: ");
		long startP = System.currentTimeMillis();
		Matrix rP = p.power(51);
		System.out.println("java took " + (System.currentTimeMillis()-startP) + "ms");
		
		Matrix rQ = p.powerNative(51);

	}
}
