class MyMeth {
  public static void myMeth() {
	int i;

	for(i=0; i<10; i++) {
		if(i == 5) return; // stop at 5
		System.out.println();
	}
  }
  
  public static void main(String args[]) {
	myMeth();
  }
}