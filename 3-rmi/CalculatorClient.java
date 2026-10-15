import java.rmi.Naming;

// Step 4: Create the client and call the remote method
// Run: java CalculatorClient   (start the server first)
public class CalculatorClient {
    public static void main(String[] args) {
        try {
            Calculator calc = (Calculator) Naming.lookup("rmi://localhost:1099/CalculatorService");

            int result = calc.add(5, 10);
            System.out.println("Result: 5 + 10 = " + result);
        } catch (Exception e) {
            System.out.println("Client exception: " + e);
        }
    }
}
