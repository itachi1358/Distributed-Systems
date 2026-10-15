import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

// Step 2: Implement the remote interface
public class CalculatorImpl extends UnicastRemoteObject implements Calculator {

    public CalculatorImpl() throws RemoteException {
        super();
    }

    public int add(int a, int b) throws RemoteException {
        System.out.println("Client requested: " + a + " + " + b);
        return a + b;
    }
}
