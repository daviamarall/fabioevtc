import java.security.InvalidAlgorithmParameterException;
import java.security.InvalidKeyException;
import java.security.NoSuchAlgorithmException;
import java.util.Base64;
import javax.crypto.BadPaddingException;
import javax.crypto.Cipher;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.KeyGenerator;
import javax.crypto.NoSuchPaddingException;
import javax.crypto.SecretKey;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;

public class TripleDESExample {
    @SuppressWarnings("CallToPrintStackTrace")
    public static void main(String[] args) {
        try {
            String plaintext = "Evertec simplificando o mercado de pagamentos";

            KeyGenerator keyGen = KeyGenerator.getInstance("DESede");
            keyGen.init(168);
            SecretKey secretKey = keyGen.generateKey();
            byte[] key = secretKey.getEncoded();

            Cipher cipher = Cipher.getInstance("DESede/CBC/PKCS5Padding");
            byte[] iv = new byte[8];
            System.arraycopy(key, 0, iv, 0, iv.length);
            IvParameterSpec ivSpec = new IvParameterSpec(iv);

            cipher.init(Cipher.ENCRYPT_MODE, new SecretKeySpec(key, "DESede"), ivSpec);
            byte[] encrypted = cipher.doFinal(plaintext.getBytes());

            System.out.println("Ciphertext: " + Base64.getEncoder().encodeToString(encrypted));

            cipher.init(Cipher.DECRYPT_MODE, new SecretKeySpec(key, "DESede"), ivSpec);
            byte[] decrypted = cipher.doFinal(encrypted);

            System.out.println("Decrypted text: " + new String(decrypted));
        } catch (InvalidAlgorithmParameterException | InvalidKeyException | NoSuchAlgorithmException | BadPaddingException | IllegalBlockSizeException | NoSuchPaddingException e) {
            e.printStackTrace();
        }
    }
}
