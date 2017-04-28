import java.util.Scanner;

public class SlotMachine {

    public static void main(String [] args) {
        Scanner keyboard = new Scanner(System.in);
        System.out.println("Hello, welcome to the slot machine");
        String play;
        int total_bet = 0, total_payout = 0;
        do {
            System.out.println("How much money are you willing to bet?");
            int bet = keyboard.nextInt();
            total_bet+=bet;
            System.out.println("\nSPINNING...SPINNING...SPINNING");
            int[] rolls = new int[3];
            rolls[0] = (int) (Math.random() * 6);
            rolls[1] = (int) (Math.random() * 6);
            rolls[2] = (int) (Math.random() * 6);

            for (int i = 0; i < 3; i++) {
                switch (rolls[i]) {
                    case 0: System.out.print("Cherries... "); break;
                    case 1: System.out.print("Oranges... ");  break;
                    case 2: System.out.print("Plums... ");    break;
                    case 3: System.out.print("Bells... ");    break;
                    case 4: System.out.print("Melons... ");   break;
                    case 5: System.out.print("Bars... ");     break;
                }
            }

            if(rolls[0] == rolls[1] && rolls[1] == rolls[2]) {
                System.out.println("\nYou Won!... Your payout is: $" + (bet * 3));
                total_payout += (bet * 3);
            }
            else if (rolls[0] == rolls[1] || rolls[0] == rolls[2] || rolls[2] == rolls[1]) {
                System.out.println("\nYou Won!... Your payout is: $" + (bet * 2));
                total_payout += (bet * 2);
            }
            else
                System.out.println("\nYou Lost!... Your payout is: $0");

            System.out.println("\nDo you you want to play again?");
            do {
                System.out.println("Either type \"Y\" to play or, \"N\" to quit.");
                play = keyboard.next().toUpperCase();
            }while ( ! (play.equals("Y") || play.equals("N")));
        }while (play.equals("Y"));
        System.out.println("Total amount bet: " + total_bet +". Total payout: " + total_payout);
    }
}
