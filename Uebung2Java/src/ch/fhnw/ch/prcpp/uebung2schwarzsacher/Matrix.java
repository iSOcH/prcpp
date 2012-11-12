package ch.fhnw.ch.prcpp.uebung2schwarzsacher;

import java.util.Random;

public class Matrix {
	private int rows, cols;

	/**
	 * holds the matrix' data<br>
	 * the element at <b>row x</b> and <b>col y</b> is stored at
	 * <b>matrix[x*cols + y]</b>
	 */
	private double[] matrix;
	
	public Matrix(int height, int width) {
		createMatrix(height, width);
		
		Random dice = new Random(56874534184132L); // typed furiously, guaranteed to be random ;)
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
	
	public boolean equals(Matrix other) {
		for (int i=0; i<cols*rows; i++) {
			if (matrix[i] != other.getElement(i)) return false;
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
		double[] result = prepareMultiplication(rows, cols, b.getWidth());
		final int rH = rows;
		final int rW = b.getWidth();
		
		for (int row=0; row<rW; row++) { // row in result
			for (int col=0; col<rH; col++) { // col in result
				for (int k=0; k<cols; k++) {
					result[row*rW + col] += matrix[row*cols + k] * b.getData()[k*rW + col];
				}
			}
		}
		
		return new Matrix(rows, b.getWidth(), result);
	}
	
	public Matrix multiplyNative(Matrix b) {
		assert rows == b.getWidth();
		double[] result = prepareMultiplication(rows, cols, b.getWidth());
		multiplyC(matrix, b.getData(), result, rows, cols, b.getWidth());
		return new Matrix(rows, b.getWidth(), result);
	}
	
	public void print() {
		for (int row=0; row<rows; row++) {
			for (int col=0; col<cols; col++) {
				System.out.print(matrix[row*cols + col]);
				System.out.print('\t');
			}
			System.out.print('\n');
		}
	}
	
	private double[] prepareMultiplication(int heightA, int widthA, int widthB) {
		return new double[heightA*widthB];
	}
	
	private native void multiplyC(double[] matrixA, double[] matrixB, double[] result,
			int heightA, int widthA, int widthB);
	
	public static void main(String[] args) {
		// example from http://de.wikipedia.org/wiki/Matrix_%28Mathematik%29#Matrizenmultiplikation
		Matrix a = new Matrix(2, 3, new double[]{1,2,3,4,5,6});
		Matrix b = new Matrix(3, 2, new double[]{6,-1,3,2,0,-3});
		Matrix r = a.multiply(b);
		r.print();
	}
}
