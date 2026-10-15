import java.rmi.Naming;
import java.rmi.registry.LocateRegistry;

// Step 3: Create the server and register the remote object
// Compile: javac *.java
// Run:     java CalculatorServer
public class CalculatorServer {
    public static void main(String[] args) {
        try {
            LocateRegistry.createRegistry(1099);

            Calculator obj = new CalculatorImpl();
            Naming.rebind("rmi://localhost:1099/CalculatorService", obj);

            System.out.println("Calculator Server is ready.");
        } catch (Exception e) {
            System.out.println("Server exception: " + e);
        }
    }
}
