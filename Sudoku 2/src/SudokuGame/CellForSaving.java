package SudokuGame;

import java.io.Serializable;

public class CellForSaving implements Serializable {

    String value;
    boolean filled;
    boolean enabled;
    java.awt.Color color;
}