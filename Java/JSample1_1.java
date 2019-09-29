/**
 * JSample1_1
 */
public class JSample1_1 {

    public static void main(String[] args) {
        long sum = 0;

        for (long i = 0; i < 1000000000; i++) {
            sum += 1;
            if (i > 100) {
                break;
            }
        }
        System.out.println("break‚¾‚æ");
        
        System.out.println("‡Œv‚Í"+ sum + "‚¾‚æ");
    }
}