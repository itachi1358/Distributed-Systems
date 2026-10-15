import java.rmi.Remote;
import java.rmi.RemoteException;

// Step 1: Create the remote interface
public interface Calculator extends Remote {
    public int add(int a, int b) throws RemoteException;
}
