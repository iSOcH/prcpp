public class Test{
		static{
			System.loadLibrary("NativeFunction"); //loads libNativeFunction.so
		}
	public static native void display();
	public static native int increment(int value);

	public static void main(String args[]){
		
		display();
		int i = increment(4);
	}
}
