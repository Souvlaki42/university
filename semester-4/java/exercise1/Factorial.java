class Factorial {
    public static long factor(int n) {        
        if (n == 0) return 0;

        if (n == 1) return 1;

        return factor(n-1) * n;
    }

    public static void main(String[] args) {
        long sum = 0;
        System.out.println("Results:");
        for (int i = 0; i < args.length; i++) {
            try {
                int num = Integer.parseInt(args[i]);
                if (num < 0) {
                    System.err.println("factorial cannot be computed for negative integer: " + num);
                }
                long factorial = factor(num);
                sum += factorial;
                System.out.println("Number: " + num + "   Factorial: " + factorial + "    Sum:    " + sum);
            } catch (NumberFormatException e) {
                System.err.println("Argument passed is not an integer: " + args[i]);
            }
        }
    }
}
