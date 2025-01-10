
import java.io.*;

public class ConcatenateFiles {

    public static void main(String[] args) {
        String file1 = "/workspaces/fabioevtc/App Concatenar Java/file1.txt";
        String file2 = "/workspaces/fabioevtc/App Concatenar Java/file2.txt";
        String outputFile = "/workspaces/fabioevtc/App Concatenar Java/Output.txt";

        File f1 = new File(file1);
        File f2 = new File(file2);

        if (!f1.exists() || !f2.exists()) {
            System.out.println("Um ou ambos arquivos não existem. Verifique os nomes e locais.");
            return;
        }

        try (BufferedReader reader1 = new BufferedReader(new FileReader(file1)); BufferedReader reader2 = new BufferedReader(new FileReader(file2)); BufferedWriter writer = new BufferedWriter(new FileWriter(outputFile))) {

            String line1, line2;
            while ((line1 = reader1.readLine()) != null & (line2 = reader2.readLine()) != null) {
                writer.write(line1 + " " + line2);
                writer.newLine();
            }
            System.out.println("Arquivos concatenados com sucesso no arquivo: " + outputFile);
        } catch (IOException e) {
        }
    }
}
