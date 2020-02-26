package SudokuGame;

import SudokuGameEngine.BadIndex;
import SudokuGameEngine.SudokuSolver;
import java.awt.Color;
import java.awt.Toolkit;
import java.io.*;
import java.util.logging.Level;
import java.util.logging.Logger;

public class MainWindow extends javax.swing.JFrame implements Serializable {

    private final int blockSize = 3;
    private final int fieldSize = blockSize * blockSize;
    private final int numberOfCells = fieldSize * fieldSize;
    private int difficulty;
    private SudokuSolver engine;
    private OverloadedCell[] cells;
    private int numberOfFilledCells;
    private int numberOfActiveCell;
    private int numberOfHints;
    private boolean hintActive;
    private final java.awt.Color hintButtonColor;
    private boolean numbersTableActive;
    private boolean saveGame;
    private boolean saveLoadActive;
    private boolean clientGameActive;

    private class NumbersTable extends javax.swing.JFrame {

        public NumbersTable() {
            initComponents();
        }

        private void initComponents() {

            jButton1 = new javax.swing.JButton();
            jButton2 = new javax.swing.JButton();
            jButton3 = new javax.swing.JButton();
            jButton4 = new javax.swing.JButton();
            jButton5 = new javax.swing.JButton();
            jButton6 = new javax.swing.JButton();
            jButton7 = new javax.swing.JButton();
            jButton8 = new javax.swing.JButton();
            jButton9 = new javax.swing.JButton();
            jButtonClear = new javax.swing.JButton();

            setAlwaysOnTop(true);
            setBackground(new java.awt.Color(102, 255, 0));
            setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
            setForeground(new java.awt.Color(102, 255, 0));
            setResizable(false);
            setType(java.awt.Window.Type.UTILITY);
            addWindowListener(new java.awt.event.WindowAdapter() {
                @Override
                public void windowClosing(java.awt.event.WindowEvent evt) {
                    formWindowClosing(evt);
                }
            });

            jButton1.setFont(new java.awt.Font("Tahoma", 1, 27));
            jButton1.setForeground(new java.awt.Color(255, 255, 0));
            jButton1.setText("1");
            jButton1.setAlignmentY(0.0F);
            jButton1.setBorderPainted(false);
            jButton1.setDefaultCapable(false);
            jButton1.setFocusPainted(false);
            jButton1.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
            jButton1.setIconTextGap(0);
            jButton1.setMargin(new java.awt.Insets(0, 0, 0, 0));
            jButton1.setMaximumSize(new java.awt.Dimension(45, 45));
            jButton1.setOpaque(false);
            jButton1.setPreferredSize(new java.awt.Dimension(45, 45));
            jButton1.setVerticalAlignment(javax.swing.SwingConstants.TOP);
            jButton1.setVerticalTextPosition(javax.swing.SwingConstants.TOP);
            jButton1.addMouseListener(new java.awt.event.MouseAdapter() {
                @Override
                public void mouseClicked(java.awt.event.MouseEvent evt) {
                    jButton1MouseClicked(evt);
                }
            });
            jButton1.addActionListener(new java.awt.event.ActionListener() {
                @Override
                public void actionPerformed(java.awt.event.ActionEvent evt) {
                    jButton1ActionPerformed(evt);
                }
            });

            jButton2.setFont(new java.awt.Font("Tahoma", 1, 27));
            jButton2.setForeground(new java.awt.Color(255, 204, 0));
            jButton2.setText("2");
            jButton2.setAlignmentY(0.0F);
            jButton2.setBorderPainted(false);
            jButton2.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
            jButton2.setIconTextGap(0);
            jButton2.setInheritsPopupMenu(true);
            jButton2.setMargin(new java.awt.Insets(0, 0, 0, 0));
            jButton2.setMaximumSize(new java.awt.Dimension(45, 45));
            jButton2.setPreferredSize(new java.awt.Dimension(45, 45));
            jButton2.setVerticalAlignment(javax.swing.SwingConstants.TOP);
            jButton2.setVerticalTextPosition(javax.swing.SwingConstants.TOP);
            jButton2.addMouseListener(new java.awt.event.MouseAdapter() {
                @Override
                public void mouseClicked(java.awt.event.MouseEvent evt) {
                    jButton2MouseClicked(evt);
                }
            });

            jButton3.setFont(new java.awt.Font("Tahoma", 1, 27));
            jButton3.setForeground(new java.awt.Color(255, 153, 0));
            jButton3.setText("3");
            jButton3.setAlignmentY(0.0F);
            jButton3.setBorderPainted(false);
            jButton3.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
            jButton3.setIconTextGap(0);
            jButton3.setMargin(new java.awt.Insets(0, 0, 0, 0));
            jButton3.setMaximumSize(new java.awt.Dimension(45, 45));
            jButton3.setPreferredSize(new java.awt.Dimension(45, 45));
            jButton3.setVerticalAlignment(javax.swing.SwingConstants.TOP);
            jButton3.setVerticalTextPosition(javax.swing.SwingConstants.TOP);
            jButton3.addMouseListener(new java.awt.event.MouseAdapter() {
                @Override
                public void mouseClicked(java.awt.event.MouseEvent evt) {
                    jButton3MouseClicked(evt);
                }
            });

            jButton4.setFont(new java.awt.Font("Tahoma", 1, 27));
            jButton4.setForeground(new java.awt.Color(255, 51, 0));
            jButton4.setText("4");
            jButton4.setAlignmentY(0.0F);
            jButton4.setBorderPainted(false);
            jButton4.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
            jButton4.setIconTextGap(0);
            jButton4.setMargin(new java.awt.Insets(0, 0, 0, 0));
            jButton4.setMaximumSize(new java.awt.Dimension(45, 45));
            jButton4.setPreferredSize(new java.awt.Dimension(45, 45));
            jButton4.setVerticalAlignment(javax.swing.SwingConstants.TOP);
            jButton4.setVerticalTextPosition(javax.swing.SwingConstants.TOP);
            jButton4.addMouseListener(new java.awt.event.MouseAdapter() {
                @Override
                public void mouseClicked(java.awt.event.MouseEvent evt) {
                    jButton4MouseClicked(evt);
                }
            });

            jButton5.setFont(new java.awt.Font("Tahoma", 1, 27));
            jButton5.setForeground(new java.awt.Color(255, 0, 153));
            jButton5.setText("5");
            jButton5.setAlignmentY(0.0F);
            jButton5.setBorderPainted(false);
            jButton5.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
            jButton5.setIconTextGap(0);
            jButton5.setMargin(new java.awt.Insets(0, 0, 0, 0));
            jButton5.setMaximumSize(new java.awt.Dimension(45, 45));
            jButton5.setPreferredSize(new java.awt.Dimension(45, 45));
            jButton5.setVerticalAlignment(javax.swing.SwingConstants.TOP);
            jButton5.setVerticalTextPosition(javax.swing.SwingConstants.TOP);
            jButton5.addMouseListener(new java.awt.event.MouseAdapter() {
                @Override
                public void mouseClicked(java.awt.event.MouseEvent evt) {
                    jButton5MouseClicked(evt);
                }
            });

            jButton6.setFont(new java.awt.Font("Tahoma", 1, 27));
            jButton6.setForeground(new java.awt.Color(255, 0, 204));
            jButton6.setText("6");
            jButton6.setAlignmentY(0.0F);
            jButton6.setBorderPainted(false);
            jButton6.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
            jButton6.setIconTextGap(0);
            jButton6.setMargin(new java.awt.Insets(0, 0, 0, 0));
            jButton6.setMaximumSize(new java.awt.Dimension(45, 45));
            jButton6.setPreferredSize(new java.awt.Dimension(45, 45));
            jButton6.setVerticalAlignment(javax.swing.SwingConstants.TOP);
            jButton6.setVerticalTextPosition(javax.swing.SwingConstants.TOP);
            jButton6.addMouseListener(new java.awt.event.MouseAdapter() {
                @Override
                public void mouseClicked(java.awt.event.MouseEvent evt) {
                    jButton6MouseClicked(evt);
                }
            });

            jButton7.setFont(new java.awt.Font("Tahoma", 1, 27));
            jButton7.setForeground(new java.awt.Color(204, 0, 255));
            jButton7.setText("7");
            jButton7.setAlignmentY(0.0F);
            jButton7.setBorderPainted(false);
            jButton7.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
            jButton7.setIconTextGap(0);
            jButton7.setMargin(new java.awt.Insets(0, 0, 0, 0));
            jButton7.setMaximumSize(new java.awt.Dimension(45, 45));
            jButton7.setPreferredSize(new java.awt.Dimension(45, 45));
            jButton7.setVerticalAlignment(javax.swing.SwingConstants.TOP);
            jButton7.setVerticalTextPosition(javax.swing.SwingConstants.TOP);
            jButton7.addMouseListener(new java.awt.event.MouseAdapter() {
                @Override
                public void mouseClicked(java.awt.event.MouseEvent evt) {
                    jButton7MouseClicked(evt);
                }
            });

            jButton8.setFont(new java.awt.Font("Tahoma", 1, 27));
            jButton8.setForeground(new java.awt.Color(153, 0, 255));
            jButton8.setText("8");
            jButton8.setAlignmentY(0.0F);
            jButton8.setBorderPainted(false);
            jButton8.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
            jButton8.setIconTextGap(0);
            jButton8.setMargin(new java.awt.Insets(0, 0, 0, 0));
            jButton8.setMaximumSize(new java.awt.Dimension(45, 45));
            jButton8.setPreferredSize(new java.awt.Dimension(45, 45));
            jButton8.setVerticalAlignment(javax.swing.SwingConstants.TOP);
            jButton8.setVerticalTextPosition(javax.swing.SwingConstants.TOP);
            jButton8.addMouseListener(new java.awt.event.MouseAdapter() {
                @Override
                public void mouseClicked(java.awt.event.MouseEvent evt) {
                    jButton8MouseClicked(evt);
                }
            });

            jButton9.setFont(new java.awt.Font("Tahoma", 1, 27));
            jButton9.setForeground(new java.awt.Color(0, 0, 204));
            jButton9.setText("9");
            jButton9.setAlignmentY(0.0F);
            jButton9.setBorderPainted(false);
            jButton9.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
            jButton9.setIconTextGap(0);
            jButton9.setMargin(new java.awt.Insets(0, 0, 0, 0));
            jButton9.setMaximumSize(new java.awt.Dimension(45, 45));
            jButton9.setPreferredSize(new java.awt.Dimension(45, 45));
            jButton9.setVerticalAlignment(javax.swing.SwingConstants.TOP);
            jButton9.setVerticalTextPosition(javax.swing.SwingConstants.TOP);
            jButton9.addMouseListener(new java.awt.event.MouseAdapter() {
                @Override
                public void mouseClicked(java.awt.event.MouseEvent evt) {
                    jButton9MouseClicked(evt);
                }
            });

            jButtonClear.setFont(new java.awt.Font("Tahoma", 1, 25));
            jButtonClear.setForeground(new java.awt.Color(0, 204, 204));
            jButtonClear.setText("Clear");
            jButtonClear.setAlignmentY(0.0F);
            jButtonClear.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
            jButtonClear.setMargin(new java.awt.Insets(0, 0, 0, 0));
            jButtonClear.setMaximumSize(new java.awt.Dimension(345, 345));
            jButtonClear.setPreferredSize(new java.awt.Dimension(149, 45));
            jButtonClear.addMouseListener(new java.awt.event.MouseAdapter() {
                @Override
                public void mouseClicked(java.awt.event.MouseEvent evt) {
                    jButtonClearMouseClicked(evt);
                }
            });

            javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
            getContentPane().setLayout(layout);
            layout.setHorizontalGroup(
                    layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING).addComponent(jButtonClear, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE).addGroup(layout.createSequentialGroup().addGap(2, 2, 2).addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING).addGroup(layout.createSequentialGroup().addComponent(jButton7, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE).addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED).addComponent(jButton8, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE).addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED).addComponent(jButton9, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)).addGroup(layout.createSequentialGroup().addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING).addComponent(jButton1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE).addComponent(jButton4, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)).addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED).addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING).addGroup(layout.createSequentialGroup().addComponent(jButton5, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE).addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED).addComponent(jButton6, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)).addGroup(layout.createSequentialGroup().addComponent(jButton2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE).addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED).addComponent(jButton3, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)))))));
            layout.setVerticalGroup(
                    layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING).addGroup(layout.createSequentialGroup().addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING).addComponent(jButton1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE).addComponent(jButton2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE).addComponent(jButton3, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)).addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED).addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE).addComponent(jButton5, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE).addComponent(jButton6, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE).addComponent(jButton4, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)).addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED).addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING).addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING).addComponent(jButton8, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE).addComponent(jButton7, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)).addComponent(jButton9, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)).addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED).addComponent(jButtonClear, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)));

            getAccessibleContext().setAccessibleParent(this);

            pack();
        }

        private void jButton1ActionPerformed(java.awt.event.ActionEvent evt) {
            actionForButtonClick(1);
        }

        private void jButton2MouseClicked(java.awt.event.MouseEvent evt) {
            actionForButtonClick(2);
        }

        private void jButton3MouseClicked(java.awt.event.MouseEvent evt) {
            actionForButtonClick(3);
        }

        private void jButton4MouseClicked(java.awt.event.MouseEvent evt) {
            actionForButtonClick(4);
        }

        private void jButton5MouseClicked(java.awt.event.MouseEvent evt) {
            actionForButtonClick(5);
        }

        private void jButton6MouseClicked(java.awt.event.MouseEvent evt) {
            actionForButtonClick(6);
        }

        private void jButton7MouseClicked(java.awt.event.MouseEvent evt) {
            actionForButtonClick(7);
        }

        private void jButton8MouseClicked(java.awt.event.MouseEvent evt) {
            actionForButtonClick(8);
        }

        private void jButton9MouseClicked(java.awt.event.MouseEvent evt) {
            actionForButtonClick(9);
        }

        private void jButtonClearMouseClicked(java.awt.event.MouseEvent evt) {
            if (!cells[numberOfActiveCell].value.getText().equals("")) {
                cells[numberOfActiveCell].value.setText("");
                --numberOfFilledCells;
                jProgressBarGameProgress.setValue(jProgressBarGameProgress.getValue() - 1);
            }
            numbersTableActive = false;
            numbersTable.setVisible(false);
        }

        private void jButton1MouseClicked(java.awt.event.MouseEvent evt) {
            actionForButtonClick(1);
        }

        private void formWindowClosing(java.awt.event.WindowEvent evt) {
            onNumbFormClose();
        }

        private void actionForButtonClick(final int number) {
            if (cells[numberOfActiveCell].value.getText().equals("")) {
                cells[numberOfActiveCell].value.setText(String.valueOf(number));
                numbersTableActive = false;
                if (numberOfFilledCells < 81) {
                    ++numberOfFilledCells;
                    jProgressBarGameProgress.setValue(jProgressBarGameProgress.getValue() + 1);
                }
                if (numberOfFilledCells == 81) {
                    if (isFilledCorrectly()) {
                        activateResult();
                    }
                }
            } else {
                cells[numberOfActiveCell].value.setText(String.valueOf(number));
                numbersTableActive = false;
                if (numberOfFilledCells == 81) {
                    if (isFilledCorrectly()) {
                        activateResult();
                    }
                }
            }
            numbersTable.setVisible(false);
        }

        private void onNumbFormClose() {
            numbersTable.setVisible(false);
            numbersTableActive = false;
        }
        private javax.swing.JButton jButton1;
        private javax.swing.JButton jButton2;
        private javax.swing.JButton jButton3;
        private javax.swing.JButton jButton4;
        private javax.swing.JButton jButton5;
        private javax.swing.JButton jButton6;
        private javax.swing.JButton jButton7;
        private javax.swing.JButton jButton8;
        private javax.swing.JButton jButton9;
        private javax.swing.JButton jButtonClear;
    }
    private NumbersTable numbersTable;

    private class SaveLoad extends javax.swing.JFrame {

        public SaveLoad() {
            initComponents();
        }

        private void initComponents() {

            jTextField1 = new javax.swing.JTextField();
            jLabelExtension = new javax.swing.JLabel();
            jButtonOK = new javax.swing.JButton();
            jButtonCancel = new javax.swing.JButton();

            setAlwaysOnTop(true);
            setBackground(new java.awt.Color(102, 255, 0));
            setForeground(new java.awt.Color(102, 255, 0));
            setResizable(false);
            setType(java.awt.Window.Type.UTILITY);
            addWindowListener(new java.awt.event.WindowAdapter() {
                @Override
                public void windowClosing(java.awt.event.WindowEvent evt) {
                    formWindowClosing(evt);
                }
            });

            jLabelExtension.setFont(new java.awt.Font("Courier New", 1, 14));
            jLabelExtension.setText(".sdk2");

            jButtonOK.setFont(new java.awt.Font("Tahoma", 0, 14));
            jButtonOK.setText("OK");
            jButtonOK.addActionListener(new java.awt.event.ActionListener() {
                @Override
                public void actionPerformed(java.awt.event.ActionEvent evt) {
                    jButtonOKActionPerformed(evt);
                }
            });

            jButtonCancel.setFont(new java.awt.Font("Tahoma", 0, 14));
            jButtonCancel.setText("Cancel");
            jButtonCancel.addActionListener(new java.awt.event.ActionListener() {
                @Override
                public void actionPerformed(java.awt.event.ActionEvent evt) {
                    jButtonCancelActionPerformed(evt);
                }
            });

            javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
            getContentPane().setLayout(layout);
            layout.setHorizontalGroup(
                    layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING).addGroup(layout.createSequentialGroup().addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING, false).addGroup(layout.createSequentialGroup().addGap(23, 23, 23).addComponent(jTextField1, javax.swing.GroupLayout.PREFERRED_SIZE, 309, javax.swing.GroupLayout.PREFERRED_SIZE).addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)).addGroup(layout.createSequentialGroup().addGap(51, 51, 51).addComponent(jButtonOK, javax.swing.GroupLayout.PREFERRED_SIZE, 100, javax.swing.GroupLayout.PREFERRED_SIZE).addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE).addComponent(jButtonCancel, javax.swing.GroupLayout.PREFERRED_SIZE, 100, javax.swing.GroupLayout.PREFERRED_SIZE).addGap(20, 20, 20))).addComponent(jLabelExtension).addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)));
            layout.setVerticalGroup(
                    layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING).addGroup(layout.createSequentialGroup().addGap(33, 33, 33).addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false).addComponent(jTextField1, javax.swing.GroupLayout.DEFAULT_SIZE, 38, Short.MAX_VALUE).addComponent(jLabelExtension, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)).addGap(18, 18, 18).addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE).addComponent(jButtonOK).addComponent(jButtonCancel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)).addContainerGap(25, Short.MAX_VALUE)));

            pack();
        }

        private void formWindowClosing(java.awt.event.WindowEvent evt) {
            onNumbFormClose();
        }

        private void onNumbFormClose() {
            saveLoadForm.setVisible(false);
            saveLoadActive = false;
        }

        private void jButtonCancelActionPerformed(java.awt.event.ActionEvent evt) {
            saveLoadActive = false;
            saveLoadForm.setVisible(false);
        }

        private void jButtonOKActionPerformed(java.awt.event.ActionEvent evt) {
            if (saveGame) {
                if (jTextField1.getText().equals("")) {
                    jTextField1.setText("New game");
                }
                try {
                    try (FileOutputStream fos = new FileOutputStream(jTextField1.getText() + ".sdk2"); ObjectOutputStream oos = new ObjectOutputStream(fos)) {
                        oos.writeInt(difficulty);
                        oos.writeObject(engine);
                        for (OverloadedCell oc : cells) {
                            CellForSaving cfs = new CellForSaving();
                            cfs.value = oc.value.getText();
                            cfs.filled = oc.filled;
                            cfs.enabled = oc.value.isEnabled();
                            cfs.color = oc.value.getBackground();
                            oos.writeObject(cfs);
                        }
                        oos.writeInt(numberOfFilledCells);
                        oos.writeInt(numberOfActiveCell);
                        oos.writeInt(numberOfHints);
                        oos.writeBoolean(hintActive);
                    }
                } catch (Exception e) {
                    System.err.println("Error writing file " + jTextField1.getText() + ".sdk2");
                }
                jTextField1.setText("");
                numbersTableActive = false;
                saveLoadActive = false;
                numbersTable.setVisible(false);
                saveLoadForm.setVisible(false);
            } else {
                try {
                    FileInputStream fis = new FileInputStream(jTextField1.getText() + ".sdk2");
                    ObjectInputStream ois = new ObjectInputStream(fis);
                    difficulty = ois.readInt();
                    engine = (SudokuSolver) ois.readObject();
                    for (OverloadedCell oc : cells) {
                        CellForSaving cfs = (CellForSaving) ois.readObject();
                        oc.value.setText(cfs.value);
                        oc.filled = cfs.filled;
                        oc.value.setEnabled(cfs.enabled);
                        oc.value.setBackground(cfs.color);
                    }
                    numberOfFilledCells = ois.readInt();
                    numberOfActiveCell = ois.readInt();
                    numberOfHints = ois.readInt();
                    hintActive = ois.readBoolean();
                    numbersTableActive = false;
                    saveLoadActive = false;
                    numbersTable.setVisible(false);
                    saveLoadForm.setVisible(false);
                    jButtonHint.setBackground(hintActive ? Color.yellow : hintButtonColor);
                    jComboBoxDifficulty.setSelectedItem(difficulty);
                    jProgressBarGameProgress.setValue(numberOfFilledCells);
                    jTextFieldNumberOfHints.setText(String.valueOf(numberOfHints));
                } catch (IOException | ClassNotFoundException e) {
                    System.err.println("Error reading from file " + jTextField1.getText() + ".sdk2");
                }
            }
            jTextField1.setText("");
            jButtonCancel.doClick();
        }
        private javax.swing.JButton jButtonOK;
        private javax.swing.JButton jButtonCancel;
        private javax.swing.JLabel jLabelExtension;
    }
    private SaveLoad saveLoadForm;

    @SuppressWarnings("LeakingThisInConstructor")
    public MainWindow() {
        this.setIconImage(Toolkit.getDefaultToolkit().getImage(this.getClass().getClassLoader().getResource("images/icon.png")));
        difficulty = 2;
        engine = new SudokuSolver(blockSize);
        engine.newGame(difficulty);
        numberOfFilledCells = 0;
        numberOfActiveCell = 0;
        numberOfHints = 0;
        hintActive = false;
        numbersTableActive = false;
        saveGame = true;
        saveLoadActive = false;
        saveGame = false;
        clientGameActive = false;
        initComponents();
        initCellArray();
        numbersTable = new NumbersTable();
        numbersTable.setLocationRelativeTo(this);
        numbersTable.setVisible(false);
        saveLoadForm = new SaveLoad();
        saveLoadForm.setLocationRelativeTo(this);
        saveLoadForm.setVisible(false);
        hintButtonColor = jButtonHint.getBackground();
        jProgressBarGameProgress.setMinimum(0);
        jProgressBarGameProgress.setMaximum(numberOfCells);
        jProgressBarGameProgress.setValue(engine.numberOfFilledCells());
        jProgressBarGameProgress.setStringPainted(true);
        jProgressBarGameProgress.setForeground(Color.orange);
        jButtonNewGame.setEnabled(true);
        jButtonRestart.setEnabled(true);
        jButtonHint.setEnabled(true);
        jButtonGiveUp.setEnabled(true);
        jButtonClientGame.setEnabled(true);
        jButtonSolve.setEnabled(false);
        jTextFieldNumberOfHints.setBackground(jPanelMain.getBackground());
    }

    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jPanelMain = new javax.swing.JPanel();
        jTextField1 = new javax.swing.JTextField();
        jTextField2 = new javax.swing.JTextField();
        jTextField3 = new javax.swing.JTextField();
        jTextField4 = new javax.swing.JTextField();
        jTextField5 = new javax.swing.JTextField();
        jTextField6 = new javax.swing.JTextField();
        jTextField7 = new javax.swing.JTextField();
        jTextField8 = new javax.swing.JTextField();
        jTextField9 = new javax.swing.JTextField();
        jTextField10 = new javax.swing.JTextField();
        jTextField11 = new javax.swing.JTextField();
        jTextField12 = new javax.swing.JTextField();
        jTextField13 = new javax.swing.JTextField();
        jTextField14 = new javax.swing.JTextField();
        jTextField15 = new javax.swing.JTextField();
        jTextField16 = new javax.swing.JTextField();
        jTextField17 = new javax.swing.JTextField();
        jTextField18 = new javax.swing.JTextField();
        jTextField19 = new javax.swing.JTextField();
        jTextField20 = new javax.swing.JTextField();
        jTextField21 = new javax.swing.JTextField();
        jTextField22 = new javax.swing.JTextField();
        jTextField23 = new javax.swing.JTextField();
        jTextField24 = new javax.swing.JTextField();
        jTextField25 = new javax.swing.JTextField();
        jTextField26 = new javax.swing.JTextField();
        jTextField27 = new javax.swing.JTextField();
        jTextField28 = new javax.swing.JTextField();
        jTextField29 = new javax.swing.JTextField();
        jTextField30 = new javax.swing.JTextField();
        jTextField31 = new javax.swing.JTextField();
        jTextField32 = new javax.swing.JTextField();
        jTextField33 = new javax.swing.JTextField();
        jTextField34 = new javax.swing.JTextField();
        jTextField35 = new javax.swing.JTextField();
        jTextField36 = new javax.swing.JTextField();
        jTextField37 = new javax.swing.JTextField();
        jTextField38 = new javax.swing.JTextField();
        jTextField39 = new javax.swing.JTextField();
        jTextField40 = new javax.swing.JTextField();
        jTextField41 = new javax.swing.JTextField();
        jTextField42 = new javax.swing.JTextField();
        jTextField43 = new javax.swing.JTextField();
        jTextField44 = new javax.swing.JTextField();
        jTextField45 = new javax.swing.JTextField();
        jTextField46 = new javax.swing.JTextField();
        jTextField47 = new javax.swing.JTextField();
        jTextField48 = new javax.swing.JTextField();
        jTextField49 = new javax.swing.JTextField();
        jTextField50 = new javax.swing.JTextField();
        jTextField51 = new javax.swing.JTextField();
        jTextField52 = new javax.swing.JTextField();
        jTextField53 = new javax.swing.JTextField();
        jTextField54 = new javax.swing.JTextField();
        jTextField55 = new javax.swing.JTextField();
        jTextField56 = new javax.swing.JTextField();
        jTextField57 = new javax.swing.JTextField();
        jTextField58 = new javax.swing.JTextField();
        jTextField59 = new javax.swing.JTextField();
        jTextField60 = new javax.swing.JTextField();
        jTextField61 = new javax.swing.JTextField();
        jTextField62 = new javax.swing.JTextField();
        jTextField63 = new javax.swing.JTextField();
        jTextField64 = new javax.swing.JTextField();
        jTextField65 = new javax.swing.JTextField();
        jTextField66 = new javax.swing.JTextField();
        jTextField67 = new javax.swing.JTextField();
        jTextField68 = new javax.swing.JTextField();
        jTextField69 = new javax.swing.JTextField();
        jTextField70 = new javax.swing.JTextField();
        jTextField71 = new javax.swing.JTextField();
        jTextField72 = new javax.swing.JTextField();
        jTextField73 = new javax.swing.JTextField();
        jTextField74 = new javax.swing.JTextField();
        jTextField75 = new javax.swing.JTextField();
        jTextField76 = new javax.swing.JTextField();
        jTextField77 = new javax.swing.JTextField();
        jTextField78 = new javax.swing.JTextField();
        jTextField79 = new javax.swing.JTextField();
        jTextField80 = new javax.swing.JTextField();
        jTextField81 = new javax.swing.JTextField();
        jPanel4 = new javax.swing.JPanel();
        jPanel5 = new javax.swing.JPanel();
        jPanel7 = new javax.swing.JPanel();
        jPanel8 = new javax.swing.JPanel();
        jPanel9 = new javax.swing.JPanel();
        jPanel10 = new javax.swing.JPanel();
        jPanel11 = new javax.swing.JPanel();
        jPanel12 = new javax.swing.JPanel();
        jPanel13 = new javax.swing.JPanel();
        jPanel14 = new javax.swing.JPanel();
        jPanel15 = new javax.swing.JPanel();
        jPanel16 = new javax.swing.JPanel();
        jButtonNewGame = new javax.swing.JButton();
        jComboBoxDifficulty = new javax.swing.JComboBox();
        jButtonClientGame = new javax.swing.JButton();
        jButtonSolve = new javax.swing.JButton();
        jButtonGiveUp = new javax.swing.JButton();
        jButtonRestart = new javax.swing.JButton();
        jButtonHint = new javax.swing.JButton();
        jLabelProgress = new javax.swing.JLabel();
        jProgressBarGameProgress = new javax.swing.JProgressBar();
        jTextFieldNumberOfHints = new javax.swing.JTextField();
        jLabelHints = new javax.swing.JLabel();
        jButtonMistakes = new javax.swing.JButton();
        jMenuBar1 = new javax.swing.JMenuBar();
        jMenu3 = new javax.swing.JMenu();
        jMenuItem1 = new javax.swing.JMenuItem();
        jMenuItem2 = new javax.swing.JMenuItem();
        jSeparator2 = new javax.swing.JPopupMenu.Separator();
        jMenuItem4 = new javax.swing.JMenuItem();
        jMenu4 = new javax.swing.JMenu();
        jMenuItem18 = new javax.swing.JMenuItem();
        jMenuItem19 = new javax.swing.JMenuItem();
        jMenuItem20 = new javax.swing.JMenuItem();
        jMenuItem24 = new javax.swing.JMenuItem();
        jMenuItem21 = new javax.swing.JMenuItem();
        jMenuItem22 = new javax.swing.JMenuItem();
        jMenuItem23 = new javax.swing.JMenuItem();
        jMenu5 = new javax.swing.JMenu();
        jMenu1 = new javax.swing.JMenu();
        jMenuItem11 = new javax.swing.JMenuItem();
        jMenuItem5 = new javax.swing.JMenuItem();
        jMenuItem9 = new javax.swing.JMenuItem();
        jMenuItem10 = new javax.swing.JMenuItem();
        jMenuItem12 = new javax.swing.JMenuItem();
        jMenuItem3 = new javax.swing.JMenuItem();
        jMenuItem16 = new javax.swing.JMenuItem();
        jMenu2 = new javax.swing.JMenu();
        jMenuItem6 = new javax.swing.JMenuItem();
        jMenuItem7 = new javax.swing.JMenuItem();
        jMenuItem8 = new javax.swing.JMenuItem();
        jMenuItem13 = new javax.swing.JMenuItem();
        jMenuItem14 = new javax.swing.JMenuItem();
        jMenuItem15 = new javax.swing.JMenuItem();
        jMenuItem17 = new javax.swing.JMenuItem();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("Sudoku 2.0");
        setAutoRequestFocus(false);
        setBackground(new java.awt.Color(0, 0, 102));
        setBounds(new java.awt.Rectangle(0, 0, 0, 0));
        setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        setMinimumSize(new java.awt.Dimension(650, 480));
        setName("FrameMain"); // NOI18N
        addWindowListener(new java.awt.event.WindowAdapter() {
            public void windowOpened(java.awt.event.WindowEvent evt) {
                formWindowOpened(evt);
            }
            public void windowActivated(java.awt.event.WindowEvent evt) {
                formWindowActivated(evt);
            }
        });

        jPanelMain.setBackground(new java.awt.Color(192, 192, 192));
        jPanelMain.setAlignmentX(0.0F);
        jPanelMain.setAlignmentY(0.0F);
        jPanelMain.setPreferredSize(new java.awt.Dimension(710, 522));

        jTextField1.setEditable(false);
        jTextField1.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField1.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField1.setAlignmentX(0.0F);
        jTextField1.setAlignmentY(0.0F);
        jTextField1.setAutoscrolls(false);
        jTextField1.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField1.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField1.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField1MouseClicked(evt);
            }
        });
        jTextField1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jTextField1ActionPerformed(evt);
            }
        });
        jTextField1.addKeyListener(new java.awt.event.KeyAdapter() {
            public void keyPressed(java.awt.event.KeyEvent evt) {
                jTextField1KeyPressed(evt);
            }
            public void keyReleased(java.awt.event.KeyEvent evt) {
                jTextField1KeyReleased(evt);
            }
        });

        jTextField2.setEditable(false);
        jTextField2.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField2.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField2.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField2.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField2.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField2MouseClicked(evt);
            }
        });
        jTextField2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jTextField2ActionPerformed(evt);
            }
        });

        jTextField3.setEditable(false);
        jTextField3.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField3.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField3.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField3.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField3.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField3MouseClicked(evt);
            }
        });

        jTextField4.setEditable(false);
        jTextField4.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField4.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField4.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField4.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField4.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField4MouseClicked(evt);
            }
        });

        jTextField5.setEditable(false);
        jTextField5.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField5.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField5.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField5.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField5.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField5MouseClicked(evt);
            }
        });

        jTextField6.setEditable(false);
        jTextField6.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField6.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField6.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField6.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField6.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField6MouseClicked(evt);
            }
        });

        jTextField7.setEditable(false);
        jTextField7.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField7.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField7.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField7.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField7.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField7MouseClicked(evt);
            }
        });

        jTextField8.setEditable(false);
        jTextField8.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField8.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField8.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField8.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField8.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField8MouseClicked(evt);
            }
        });

        jTextField9.setEditable(false);
        jTextField9.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField9.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField9.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField9.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField9.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField9MouseClicked(evt);
            }
        });

        jTextField10.setEditable(false);
        jTextField10.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField10.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField10.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField10.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField10.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField10MouseClicked(evt);
            }
        });

        jTextField11.setEditable(false);
        jTextField11.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField11.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField11.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField11.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField11.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField11MouseClicked(evt);
            }
        });

        jTextField12.setEditable(false);
        jTextField12.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField12.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField12.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField12.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField12.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField12MouseClicked(evt);
            }
        });

        jTextField13.setEditable(false);
        jTextField13.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField13.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField13.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField13.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField13.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField13MouseClicked(evt);
            }
        });

        jTextField14.setEditable(false);
        jTextField14.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField14.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField14.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField14.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField14.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField14MouseClicked(evt);
            }
        });

        jTextField15.setEditable(false);
        jTextField15.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField15.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField15.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField15.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField15.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField15MouseClicked(evt);
            }
        });

        jTextField16.setEditable(false);
        jTextField16.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField16.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField16.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField16.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField16.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField16MouseClicked(evt);
            }
        });
        jTextField16.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jTextField16ActionPerformed(evt);
            }
        });

        jTextField17.setEditable(false);
        jTextField17.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField17.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField17.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField17.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField17.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField17MouseClicked(evt);
            }
        });

        jTextField18.setEditable(false);
        jTextField18.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField18.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField18.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField18.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField18.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField18MouseClicked(evt);
            }
        });

        jTextField19.setEditable(false);
        jTextField19.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField19.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField19.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField19.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField19.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField19MouseClicked(evt);
            }
        });

        jTextField20.setEditable(false);
        jTextField20.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField20.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField20.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField20.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField20.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField20MouseClicked(evt);
            }
        });

        jTextField21.setEditable(false);
        jTextField21.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField21.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField21.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField21.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField21.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField21MouseClicked(evt);
            }
        });

        jTextField22.setEditable(false);
        jTextField22.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField22.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField22.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField22.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField22.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField22MouseClicked(evt);
            }
        });

        jTextField23.setEditable(false);
        jTextField23.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField23.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField23.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField23.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField23.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField23MouseClicked(evt);
            }
        });

        jTextField24.setEditable(false);
        jTextField24.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField24.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField24.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField24.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField24.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField24MouseClicked(evt);
            }
        });

        jTextField25.setEditable(false);
        jTextField25.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField25.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField25.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField25.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField25.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField25MouseClicked(evt);
            }
        });

        jTextField26.setEditable(false);
        jTextField26.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField26.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField26.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField26.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField26.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField26MouseClicked(evt);
            }
        });

        jTextField27.setEditable(false);
        jTextField27.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField27.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField27.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField27.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField27.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField27MouseClicked(evt);
            }
        });

        jTextField28.setEditable(false);
        jTextField28.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField28.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField28.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField28.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField28.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField28MouseClicked(evt);
            }
        });

        jTextField29.setEditable(false);
        jTextField29.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField29.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField29.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField29.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField29.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField29MouseClicked(evt);
            }
        });

        jTextField30.setEditable(false);
        jTextField30.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField30.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField30.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField30.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField30.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField30MouseClicked(evt);
            }
        });

        jTextField31.setEditable(false);
        jTextField31.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField31.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField31.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField31.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField31.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField31MouseClicked(evt);
            }
        });

        jTextField32.setEditable(false);
        jTextField32.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField32.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField32.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField32.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField32.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField32MouseClicked(evt);
            }
        });

        jTextField33.setEditable(false);
        jTextField33.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField33.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField33.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField33.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField33.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField33MouseClicked(evt);
            }
        });

        jTextField34.setEditable(false);
        jTextField34.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField34.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField34.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField34.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField34.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField34MouseClicked(evt);
            }
        });

        jTextField35.setEditable(false);
        jTextField35.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField35.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField35.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField35.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField35.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField35MouseClicked(evt);
            }
        });

        jTextField36.setEditable(false);
        jTextField36.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField36.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField36.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField36.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField36.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField36MouseClicked(evt);
            }
        });

        jTextField37.setEditable(false);
        jTextField37.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField37.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField37.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField37.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField37.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField37MouseClicked(evt);
            }
        });

        jTextField38.setEditable(false);
        jTextField38.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField38.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField38.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField38.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField38.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField38MouseClicked(evt);
            }
        });

        jTextField39.setEditable(false);
        jTextField39.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField39.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField39.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField39.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField39.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField39MouseClicked(evt);
            }
        });

        jTextField40.setEditable(false);
        jTextField40.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField40.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField40.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField40.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField40.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField40MouseClicked(evt);
            }
        });

        jTextField41.setEditable(false);
        jTextField41.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField41.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField41.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField41.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField41.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField41MouseClicked(evt);
            }
        });

        jTextField42.setEditable(false);
        jTextField42.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField42.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField42.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField42.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField42.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField42MouseClicked(evt);
            }
        });

        jTextField43.setEditable(false);
        jTextField43.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField43.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField43.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField43.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField43.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField43MouseClicked(evt);
            }
        });

        jTextField44.setEditable(false);
        jTextField44.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField44.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField44.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField44.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField44.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField44MouseClicked(evt);
            }
        });

        jTextField45.setEditable(false);
        jTextField45.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField45.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField45.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField45.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField45.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField45MouseClicked(evt);
            }
        });

        jTextField46.setEditable(false);
        jTextField46.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField46.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField46.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField46.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField46.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField46MouseClicked(evt);
            }
        });

        jTextField47.setEditable(false);
        jTextField47.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField47.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField47.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField47.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField47.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField47MouseClicked(evt);
            }
        });

        jTextField48.setEditable(false);
        jTextField48.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField48.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField48.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField48.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField48.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField48MouseClicked(evt);
            }
        });

        jTextField49.setEditable(false);
        jTextField49.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField49.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField49.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField49.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField49.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField49MouseClicked(evt);
            }
        });

        jTextField50.setEditable(false);
        jTextField50.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField50.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField50.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField50.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField50.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField50MouseClicked(evt);
            }
        });

        jTextField51.setEditable(false);
        jTextField51.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField51.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField51.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField51.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField51.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField51MouseClicked(evt);
            }
        });

        jTextField52.setEditable(false);
        jTextField52.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField52.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField52.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField52.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField52.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField52MouseClicked(evt);
            }
        });

        jTextField53.setEditable(false);
        jTextField53.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField53.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField53.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField53.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField53.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField53MouseClicked(evt);
            }
        });

        jTextField54.setEditable(false);
        jTextField54.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField54.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField54.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField54.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField54.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField54MouseClicked(evt);
            }
        });

        jTextField55.setEditable(false);
        jTextField55.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField55.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField55.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField55.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField55.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField55MouseClicked(evt);
            }
        });

        jTextField56.setEditable(false);
        jTextField56.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField56.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField56.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField56.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField56.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField56MouseClicked(evt);
            }
        });

        jTextField57.setEditable(false);
        jTextField57.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField57.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField57.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField57.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField57.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField57MouseClicked(evt);
            }
        });

        jTextField58.setEditable(false);
        jTextField58.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField58.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField58.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField58.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField58.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField58MouseClicked(evt);
            }
        });

        jTextField59.setEditable(false);
        jTextField59.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField59.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField59.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField59.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField59.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField59MouseClicked(evt);
            }
        });

        jTextField60.setEditable(false);
        jTextField60.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField60.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField60.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField60.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField60.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField60MouseClicked(evt);
            }
        });

        jTextField61.setEditable(false);
        jTextField61.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField61.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField61.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField61.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField61.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField61MouseClicked(evt);
            }
        });

        jTextField62.setEditable(false);
        jTextField62.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField62.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField62.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField62.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField62.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField62MouseClicked(evt);
            }
        });

        jTextField63.setEditable(false);
        jTextField63.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField63.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField63.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField63.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField63.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField63MouseClicked(evt);
            }
        });

        jTextField64.setEditable(false);
        jTextField64.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField64.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField64.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField64.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField64.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField64MouseClicked(evt);
            }
        });

        jTextField65.setEditable(false);
        jTextField65.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField65.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField65.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField65.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField65.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField65MouseClicked(evt);
            }
        });

        jTextField66.setEditable(false);
        jTextField66.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField66.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField66.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField66.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField66.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField66MouseClicked(evt);
            }
        });

        jTextField67.setEditable(false);
        jTextField67.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField67.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField67.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField67.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField67.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField67MouseClicked(evt);
            }
        });

        jTextField68.setEditable(false);
        jTextField68.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField68.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField68.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField68.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField68.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField68MouseClicked(evt);
            }
        });

        jTextField69.setEditable(false);
        jTextField69.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField69.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField69.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField69.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField69.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField69MouseClicked(evt);
            }
        });

        jTextField70.setEditable(false);
        jTextField70.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField70.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField70.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField70.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField70.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField70MouseClicked(evt);
            }
        });

        jTextField71.setEditable(false);
        jTextField71.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField71.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField71.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField71.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField71.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField71MouseClicked(evt);
            }
        });

        jTextField72.setEditable(false);
        jTextField72.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField72.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField72.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField72.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField72.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField72MouseClicked(evt);
            }
        });

        jTextField73.setEditable(false);
        jTextField73.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField73.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField73.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField73.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField73.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField73MouseClicked(evt);
            }
        });

        jTextField74.setEditable(false);
        jTextField74.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField74.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField74.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField74.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField74.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField74MouseClicked(evt);
            }
        });

        jTextField75.setEditable(false);
        jTextField75.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField75.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField75.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField75.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField75.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField75MouseClicked(evt);
            }
        });

        jTextField76.setEditable(false);
        jTextField76.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField76.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField76.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField76.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField76.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField76MouseClicked(evt);
            }
        });

        jTextField77.setEditable(false);
        jTextField77.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField77.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField77.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField77.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField77.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField77MouseClicked(evt);
            }
        });

        jTextField78.setEditable(false);
        jTextField78.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField78.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField78.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField78.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField78.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField78MouseClicked(evt);
            }
        });

        jTextField79.setEditable(false);
        jTextField79.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField79.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField79.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField79.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField79.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField79MouseClicked(evt);
            }
        });

        jTextField80.setEditable(false);
        jTextField80.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField80.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField80.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField80.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField80.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField80MouseClicked(evt);
            }
        });

        jTextField81.setEditable(false);
        jTextField81.setFont(new java.awt.Font("Tahoma", 1, 40)); // NOI18N
        jTextField81.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextField81.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jTextField81.setPreferredSize(new java.awt.Dimension(45, 45));
        jTextField81.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTextField81MouseClicked(evt);
            }
        });

        jPanel4.setBackground(new java.awt.Color(128, 128, 128));
        jPanel4.setForeground(new java.awt.Color(102, 255, 102));
        jPanel4.setPreferredSize(new java.awt.Dimension(7, 147));

        javax.swing.GroupLayout jPanel4Layout = new javax.swing.GroupLayout(jPanel4);
        jPanel4.setLayout(jPanel4Layout);
        jPanel4Layout.setHorizontalGroup(
            jPanel4Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 7, Short.MAX_VALUE)
        );
        jPanel4Layout.setVerticalGroup(
            jPanel4Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 147, Short.MAX_VALUE)
        );

        jPanel5.setBackground(new java.awt.Color(128, 128, 128));
        jPanel5.setForeground(new java.awt.Color(102, 255, 102));
        jPanel5.setPreferredSize(new java.awt.Dimension(7, 147));

        javax.swing.GroupLayout jPanel5Layout = new javax.swing.GroupLayout(jPanel5);
        jPanel5.setLayout(jPanel5Layout);
        jPanel5Layout.setHorizontalGroup(
            jPanel5Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 7, Short.MAX_VALUE)
        );
        jPanel5Layout.setVerticalGroup(
            jPanel5Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 147, Short.MAX_VALUE)
        );

        jPanel7.setBackground(new java.awt.Color(128, 128, 128));
        jPanel7.setPreferredSize(new java.awt.Dimension(147, 7));

        javax.swing.GroupLayout jPanel7Layout = new javax.swing.GroupLayout(jPanel7);
        jPanel7.setLayout(jPanel7Layout);
        jPanel7Layout.setHorizontalGroup(
            jPanel7Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 147, Short.MAX_VALUE)
        );
        jPanel7Layout.setVerticalGroup(
            jPanel7Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 7, Short.MAX_VALUE)
        );

        jPanel8.setBackground(new java.awt.Color(128, 128, 128));
        jPanel8.setPreferredSize(new java.awt.Dimension(147, 7));

        javax.swing.GroupLayout jPanel8Layout = new javax.swing.GroupLayout(jPanel8);
        jPanel8.setLayout(jPanel8Layout);
        jPanel8Layout.setHorizontalGroup(
            jPanel8Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 147, Short.MAX_VALUE)
        );
        jPanel8Layout.setVerticalGroup(
            jPanel8Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 7, Short.MAX_VALUE)
        );

        jPanel9.setBackground(new java.awt.Color(128, 128, 128));
        jPanel9.setPreferredSize(new java.awt.Dimension(147, 7));

        javax.swing.GroupLayout jPanel9Layout = new javax.swing.GroupLayout(jPanel9);
        jPanel9.setLayout(jPanel9Layout);
        jPanel9Layout.setHorizontalGroup(
            jPanel9Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 147, Short.MAX_VALUE)
        );
        jPanel9Layout.setVerticalGroup(
            jPanel9Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 7, Short.MAX_VALUE)
        );

        jPanel10.setBackground(new java.awt.Color(128, 128, 128));
        jPanel10.setPreferredSize(new java.awt.Dimension(7, 147));

        javax.swing.GroupLayout jPanel10Layout = new javax.swing.GroupLayout(jPanel10);
        jPanel10.setLayout(jPanel10Layout);
        jPanel10Layout.setHorizontalGroup(
            jPanel10Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 7, Short.MAX_VALUE)
        );
        jPanel10Layout.setVerticalGroup(
            jPanel10Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 147, Short.MAX_VALUE)
        );

        jPanel11.setBackground(new java.awt.Color(128, 128, 128));
        jPanel11.setPreferredSize(new java.awt.Dimension(7, 147));

        javax.swing.GroupLayout jPanel11Layout = new javax.swing.GroupLayout(jPanel11);
        jPanel11.setLayout(jPanel11Layout);
        jPanel11Layout.setHorizontalGroup(
            jPanel11Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 7, Short.MAX_VALUE)
        );
        jPanel11Layout.setVerticalGroup(
            jPanel11Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 147, Short.MAX_VALUE)
        );

        jPanel12.setBackground(new java.awt.Color(128, 128, 128));
        jPanel12.setPreferredSize(new java.awt.Dimension(147, 7));

        javax.swing.GroupLayout jPanel12Layout = new javax.swing.GroupLayout(jPanel12);
        jPanel12.setLayout(jPanel12Layout);
        jPanel12Layout.setHorizontalGroup(
            jPanel12Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 147, Short.MAX_VALUE)
        );
        jPanel12Layout.setVerticalGroup(
            jPanel12Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 7, Short.MAX_VALUE)
        );

        jPanel13.setBackground(new java.awt.Color(128, 128, 128));
        jPanel13.setPreferredSize(new java.awt.Dimension(147, 7));

        javax.swing.GroupLayout jPanel13Layout = new javax.swing.GroupLayout(jPanel13);
        jPanel13.setLayout(jPanel13Layout);
        jPanel13Layout.setHorizontalGroup(
            jPanel13Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 147, Short.MAX_VALUE)
        );
        jPanel13Layout.setVerticalGroup(
            jPanel13Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 7, Short.MAX_VALUE)
        );

        jPanel14.setBackground(new java.awt.Color(128, 128, 128));
        jPanel14.setPreferredSize(new java.awt.Dimension(147, 7));

        javax.swing.GroupLayout jPanel14Layout = new javax.swing.GroupLayout(jPanel14);
        jPanel14.setLayout(jPanel14Layout);
        jPanel14Layout.setHorizontalGroup(
            jPanel14Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 147, Short.MAX_VALUE)
        );
        jPanel14Layout.setVerticalGroup(
            jPanel14Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 7, Short.MAX_VALUE)
        );

        jPanel15.setBackground(new java.awt.Color(128, 128, 128));
        jPanel15.setPreferredSize(new java.awt.Dimension(7, 147));

        javax.swing.GroupLayout jPanel15Layout = new javax.swing.GroupLayout(jPanel15);
        jPanel15.setLayout(jPanel15Layout);
        jPanel15Layout.setHorizontalGroup(
            jPanel15Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 7, Short.MAX_VALUE)
        );
        jPanel15Layout.setVerticalGroup(
            jPanel15Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 147, Short.MAX_VALUE)
        );

        jPanel16.setBackground(new java.awt.Color(128, 128, 128));
        jPanel16.setPreferredSize(new java.awt.Dimension(7, 147));

        javax.swing.GroupLayout jPanel16Layout = new javax.swing.GroupLayout(jPanel16);
        jPanel16.setLayout(jPanel16Layout);
        jPanel16Layout.setHorizontalGroup(
            jPanel16Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 7, Short.MAX_VALUE)
        );
        jPanel16Layout.setVerticalGroup(
            jPanel16Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 147, Short.MAX_VALUE)
        );

        jButtonNewGame.setFont(new java.awt.Font("Tahoma", 1, 18)); // NOI18N
        jButtonNewGame.setForeground(new java.awt.Color(0, 102, 102));
        jButtonNewGame.setText("New Game");
        jButtonNewGame.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButtonNewGameActionPerformed(evt);
            }
        });

        jComboBoxDifficulty.setBackground(java.awt.Color.yellow);
        jComboBoxDifficulty.setFont(new java.awt.Font("Segoe Script", 3, 18)); // NOI18N
        jComboBoxDifficulty.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "Very Easy", "Easy", "Medium", "Hard", "Very Hard" }));
        jComboBoxDifficulty.setSelectedIndex(2);
        jComboBoxDifficulty.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jComboBoxDifficultyActionPerformed(evt);
            }
        });

        jButtonClientGame.setFont(new java.awt.Font("Tahoma", 1, 18)); // NOI18N
        jButtonClientGame.setForeground(new java.awt.Color(255, 0, 204));
        jButtonClientGame.setText("My Puzzle");
        jButtonClientGame.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
        jButtonClientGame.setPreferredSize(new java.awt.Dimension(155, 40));
        jButtonClientGame.setRequestFocusEnabled(false);
        jButtonClientGame.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButtonClientGameActionPerformed(evt);
            }
        });

        jButtonSolve.setFont(new java.awt.Font("Tahoma", 1, 18)); // NOI18N
        jButtonSolve.setForeground(new java.awt.Color(102, 51, 255));
        jButtonSolve.setText("Solve");
        jButtonSolve.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
        jButtonSolve.setPreferredSize(new java.awt.Dimension(150, 36));
        jButtonSolve.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButtonSolveActionPerformed(evt);
            }
        });

        jButtonGiveUp.setFont(new java.awt.Font("Tahoma", 1, 18)); // NOI18N
        jButtonGiveUp.setForeground(new java.awt.Color(255, 102, 102));
        jButtonGiveUp.setText("Give Up");
        jButtonGiveUp.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButtonGiveUpActionPerformed(evt);
            }
        });

        jButtonRestart.setFont(new java.awt.Font("Tahoma", 1, 18)); // NOI18N
        jButtonRestart.setForeground(new java.awt.Color(0, 204, 102));
        jButtonRestart.setText("Restart");
        jButtonRestart.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButtonRestartActionPerformed(evt);
            }
        });

        jButtonHint.setFont(new java.awt.Font("Tahoma", 1, 18)); // NOI18N
        jButtonHint.setForeground(new java.awt.Color(153, 153, 0));
        jButtonHint.setText("Hint");
        jButtonHint.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButtonHintActionPerformed(evt);
            }
        });

        jLabelProgress.setFont(new java.awt.Font("Segoe Script", 0, 18)); // NOI18N
        jLabelProgress.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        jLabelProgress.setText("Progress");
        jLabelProgress.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);

        jProgressBarGameProgress.setBackground(new java.awt.Color(255, 255, 255));
        jProgressBarGameProgress.setForeground(java.awt.Color.gray);
        jProgressBarGameProgress.setBorderPainted(false);
        jProgressBarGameProgress.setStringPainted(true);

        jTextFieldNumberOfHints.setBackground(new java.awt.Color(153, 153, 153));
        jTextFieldNumberOfHints.setFont(new java.awt.Font("Tempus Sans ITC", 0, 18)); // NOI18N
        jTextFieldNumberOfHints.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        jTextFieldNumberOfHints.setText("0");
        jTextFieldNumberOfHints.setAutoscrolls(false);
        jTextFieldNumberOfHints.setBorder(null);
        jTextFieldNumberOfHints.setCursor(new java.awt.Cursor(java.awt.Cursor.NE_RESIZE_CURSOR));
        jTextFieldNumberOfHints.setEnabled(false);
        jTextFieldNumberOfHints.setOpaque(false);
        jTextFieldNumberOfHints.setSelectionColor(new java.awt.Color(204, 204, 204));

        jLabelHints.setBackground(new java.awt.Color(204, 204, 204));
        jLabelHints.setFont(new java.awt.Font("Segoe Script", 0, 18)); // NOI18N
        jLabelHints.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        jLabelHints.setText("Hints:");

        jButtonMistakes.setFont(new java.awt.Font("Tahoma", 1, 18)); // NOI18N
        jButtonMistakes.setForeground(new java.awt.Color(255, 255, 51));
        jButtonMistakes.setText("Fix");
        jButtonMistakes.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButtonMistakesActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout jPanelMainLayout = new javax.swing.GroupLayout(jPanelMain);
        jPanelMain.setLayout(jPanelMainLayout);
        jPanelMainLayout.setHorizontalGroup(
            jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanelMainLayout.createSequentialGroup()
                .addGap(18, 18, 18)
                .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(jPanelMainLayout.createSequentialGroup()
                        .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addGroup(jPanelMainLayout.createSequentialGroup()
                                .addComponent(jTextField28, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(jTextField29, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(jTextField30, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                            .addGroup(jPanelMainLayout.createSequentialGroup()
                                .addComponent(jTextField37, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(jTextField38, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(jTextField39, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                            .addGroup(jPanelMainLayout.createSequentialGroup()
                                .addComponent(jTextField46, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(jTextField47, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(jTextField48, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(jPanel10, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addGroup(jPanelMainLayout.createSequentialGroup()
                                .addComponent(jTextField31, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(jTextField32, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(jTextField33, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                            .addGroup(jPanelMainLayout.createSequentialGroup()
                                .addComponent(jTextField40, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(jTextField41, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(jTextField42, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                            .addGroup(jPanelMainLayout.createSequentialGroup()
                                .addComponent(jTextField49, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(jTextField50, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(jTextField51, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(jPanel11, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(jTextField34, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(jTextField43, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(jTextField52, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addGroup(jPanelMainLayout.createSequentialGroup()
                                .addComponent(jTextField35, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(jTextField36, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                            .addGroup(jPanelMainLayout.createSequentialGroup()
                                .addComponent(jTextField44, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(jTextField45, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                            .addGroup(jPanelMainLayout.createSequentialGroup()
                                .addComponent(jTextField53, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(jTextField54, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))))
                    .addGroup(jPanelMainLayout.createSequentialGroup()
                        .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(jPanel7, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addGroup(jPanelMainLayout.createSequentialGroup()
                                .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addGroup(jPanelMainLayout.createSequentialGroup()
                                        .addComponent(jTextField1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                        .addComponent(jTextField2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                        .addComponent(jTextField3, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                                    .addGroup(jPanelMainLayout.createSequentialGroup()
                                        .addComponent(jTextField10, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                        .addComponent(jTextField11, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                        .addComponent(jTextField12, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                                    .addGroup(jPanelMainLayout.createSequentialGroup()
                                        .addComponent(jTextField19, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                        .addComponent(jTextField20, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                        .addComponent(jTextField21, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)))
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(jPanel4, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                .addComponent(jPanel8, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addGroup(jPanelMainLayout.createSequentialGroup()
                                    .addComponent(jTextField22, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                    .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                    .addComponent(jTextField23, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                    .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                    .addComponent(jTextField24, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)))
                            .addGroup(jPanelMainLayout.createSequentialGroup()
                                .addComponent(jTextField4, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(jTextField5, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(jTextField6, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                            .addGroup(jPanelMainLayout.createSequentialGroup()
                                .addComponent(jTextField13, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(jTextField14, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(jTextField15, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(jPanel5, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addGroup(jPanelMainLayout.createSequentialGroup()
                                .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addComponent(jTextField7, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                    .addComponent(jTextField16, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                    .addComponent(jTextField25, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                                .addGap(0, 0, Short.MAX_VALUE)
                                .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, jPanelMainLayout.createSequentialGroup()
                                        .addComponent(jTextField17, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                        .addComponent(jTextField18, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, jPanelMainLayout.createSequentialGroup()
                                        .addComponent(jTextField26, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                        .addComponent(jTextField27, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, jPanelMainLayout.createSequentialGroup()
                                        .addComponent(jTextField8, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                        .addComponent(jTextField9, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))))
                            .addComponent(jPanel9, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)))
                    .addGroup(jPanelMainLayout.createSequentialGroup()
                        .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING, false)
                            .addGroup(javax.swing.GroupLayout.Alignment.LEADING, jPanelMainLayout.createSequentialGroup()
                                .addComponent(jPanel12, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addGap(18, 18, 18)
                                .addComponent(jPanel13, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                .addComponent(jPanel14, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                            .addGroup(javax.swing.GroupLayout.Alignment.LEADING, jPanelMainLayout.createSequentialGroup()
                                .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addGroup(jPanelMainLayout.createSequentialGroup()
                                        .addComponent(jTextField73, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                        .addComponent(jTextField74, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                        .addComponent(jTextField75, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                                    .addGroup(jPanelMainLayout.createSequentialGroup()
                                        .addComponent(jTextField64, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                        .addComponent(jTextField65, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                        .addComponent(jTextField66, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                                    .addGroup(jPanelMainLayout.createSequentialGroup()
                                        .addComponent(jTextField55, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                        .addComponent(jTextField56, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                        .addComponent(jTextField57, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)))
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(jPanel15, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addComponent(jTextField76, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                    .addComponent(jTextField67, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                    .addComponent(jTextField58, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addGroup(jPanelMainLayout.createSequentialGroup()
                                        .addComponent(jTextField77, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                        .addComponent(jTextField78, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                                    .addGroup(jPanelMainLayout.createSequentialGroup()
                                        .addComponent(jTextField59, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                        .addComponent(jTextField60, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                                    .addGroup(jPanelMainLayout.createSequentialGroup()
                                        .addComponent(jTextField68, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                        .addComponent(jTextField69, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)))
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(jPanel16, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addGroup(jPanelMainLayout.createSequentialGroup()
                                        .addComponent(jTextField61, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                        .addComponent(jTextField62, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                        .addComponent(jTextField63, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                                    .addGroup(jPanelMainLayout.createSequentialGroup()
                                        .addComponent(jTextField79, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                        .addComponent(jTextField80, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                        .addComponent(jTextField81, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                                    .addGroup(jPanelMainLayout.createSequentialGroup()
                                        .addComponent(jTextField70, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                        .addComponent(jTextField71, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                        .addComponent(jTextField72, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)))))
                        .addGap(0, 0, Short.MAX_VALUE)))
                .addGap(31, 31, 31)
                .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(jPanelMainLayout.createSequentialGroup()
                        .addComponent(jLabelHints, javax.swing.GroupLayout.PREFERRED_SIZE, 93, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(jTextFieldNumberOfHints, javax.swing.GroupLayout.PREFERRED_SIZE, 53, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addComponent(jComboBoxDifficulty, javax.swing.GroupLayout.PREFERRED_SIZE, 150, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(jProgressBarGameProgress, javax.swing.GroupLayout.PREFERRED_SIZE, 150, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(jLabelProgress, javax.swing.GroupLayout.PREFERRED_SIZE, 150, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(jButtonNewGame, javax.swing.GroupLayout.PREFERRED_SIZE, 150, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(jButtonRestart, javax.swing.GroupLayout.PREFERRED_SIZE, 150, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(jButtonHint, javax.swing.GroupLayout.PREFERRED_SIZE, 150, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(jButtonMistakes, javax.swing.GroupLayout.PREFERRED_SIZE, 150, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(jButtonGiveUp, javax.swing.GroupLayout.PREFERRED_SIZE, 150, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(jButtonClientGame, javax.swing.GroupLayout.PREFERRED_SIZE, 150, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(jButtonSolve, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(21, 21, 21))
        );
        jPanelMainLayout.setVerticalGroup(
            jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanelMainLayout.createSequentialGroup()
                .addGap(5, 5, 5)
                .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jComboBoxDifficulty, javax.swing.GroupLayout.PREFERRED_SIZE, 35, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addGroup(jPanelMainLayout.createSequentialGroup()
                        .addGap(13, 13, 13)
                        .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addGroup(jPanelMainLayout.createSequentialGroup()
                                .addGap(166, 166, 166)
                                .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addGroup(jPanelMainLayout.createSequentialGroup()
                                        .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                            .addGroup(jPanelMainLayout.createSequentialGroup()
                                                .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                                    .addComponent(jTextField31, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                    .addComponent(jTextField32, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                    .addComponent(jTextField33, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                                .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                                    .addComponent(jTextField42, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                    .addComponent(jTextField40, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                    .addComponent(jTextField41, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                                .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                                    .addComponent(jTextField49, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                    .addComponent(jTextField50, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                    .addComponent(jTextField51, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)))
                                            .addComponent(jPanel10, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                            .addComponent(jPanel11, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                        .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                                            .addComponent(jPanel12, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                            .addComponent(jPanel14, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                            .addComponent(jPanel13, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                        .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                            .addComponent(jPanel15, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                            .addComponent(jPanel16, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                            .addGroup(jPanelMainLayout.createSequentialGroup()
                                                .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                                    .addComponent(jTextField55, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                    .addComponent(jTextField56, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                    .addComponent(jTextField57, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                    .addComponent(jTextField58, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                    .addComponent(jTextField59, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                    .addComponent(jTextField60, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                    .addComponent(jTextField61, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                    .addComponent(jTextField62, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                    .addComponent(jTextField63, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                                .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                                    .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                                        .addComponent(jTextField64, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                        .addComponent(jTextField65, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                        .addComponent(jTextField66, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                                                    .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                                        .addComponent(jTextField67, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                        .addComponent(jTextField68, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                        .addComponent(jTextField69, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                                                    .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                                        .addComponent(jTextField70, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                        .addComponent(jTextField71, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                        .addComponent(jTextField72, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)))
                                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                                .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                                        .addComponent(jTextField76, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                        .addComponent(jTextField77, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                        .addComponent(jTextField78, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                        .addComponent(jTextField79, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                                                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                                        .addComponent(jTextField81, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                        .addComponent(jTextField80, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                                                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                                        .addComponent(jTextField75, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                        .addComponent(jTextField74, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                        .addComponent(jTextField73, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))))))
                                    .addGroup(jPanelMainLayout.createSequentialGroup()
                                        .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                            .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                                .addComponent(jTextField28, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                .addComponent(jTextField30, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                                            .addComponent(jTextField29, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                        .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                            .addComponent(jTextField37, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                            .addComponent(jTextField38, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                            .addComponent(jTextField39, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                        .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                            .addComponent(jTextField46, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                            .addComponent(jTextField47, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                            .addComponent(jTextField48, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)))))
                            .addGroup(jPanelMainLayout.createSequentialGroup()
                                .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addGroup(jPanelMainLayout.createSequentialGroup()
                                        .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                            .addGroup(jPanelMainLayout.createSequentialGroup()
                                                .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                                    .addComponent(jTextField1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                    .addComponent(jTextField2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                    .addComponent(jTextField3, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                                .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                                    .addComponent(jTextField10, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                    .addComponent(jTextField11, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                    .addComponent(jTextField12, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                                .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                                    .addComponent(jTextField19, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                    .addComponent(jTextField20, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                    .addComponent(jTextField21, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)))
                                            .addGroup(jPanelMainLayout.createSequentialGroup()
                                                .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                                    .addComponent(jTextField6, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                    .addComponent(jTextField5, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                    .addComponent(jTextField4, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                                .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                                    .addComponent(jTextField13, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                    .addComponent(jTextField14, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                    .addComponent(jTextField15, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                                .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                                    .addComponent(jTextField22, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                    .addComponent(jTextField23, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                    .addComponent(jTextField24, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)))
                                            .addComponent(jPanel4, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                            .addGroup(jPanelMainLayout.createSequentialGroup()
                                                .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                                    .addComponent(jTextField9, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                    .addComponent(jTextField8, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                    .addComponent(jTextField7, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                                .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                                    .addComponent(jTextField16, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                    .addComponent(jTextField17, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                    .addComponent(jTextField18, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                                .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                                    .addComponent(jTextField25, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                    .addComponent(jTextField26, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                    .addComponent(jTextField27, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))))
                                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                        .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                                            .addComponent(jPanel7, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                            .addComponent(jPanel9, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                            .addComponent(jPanel8, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)))
                                    .addComponent(jPanel5, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                                .addGap(6, 6, 6)
                                .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addComponent(jTextField34, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                    .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                        .addComponent(jTextField36, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addComponent(jTextField35, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)))
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                    .addComponent(jTextField43, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                    .addComponent(jTextField44, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                    .addComponent(jTextField45, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                    .addComponent(jTextField52, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                    .addComponent(jTextField53, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                    .addComponent(jTextField54, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)))
                            .addGroup(jPanelMainLayout.createSequentialGroup()
                                .addGap(33, 33, 33)
                                .addComponent(jLabelProgress, javax.swing.GroupLayout.PREFERRED_SIZE, 28, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(jProgressBarGameProgress, javax.swing.GroupLayout.PREFERRED_SIZE, 31, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addGap(8, 8, 8)
                                .addGroup(jPanelMainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                    .addComponent(jTextFieldNumberOfHints, javax.swing.GroupLayout.PREFERRED_SIZE, 30, javax.swing.GroupLayout.PREFERRED_SIZE)
                                    .addComponent(jLabelHints, javax.swing.GroupLayout.PREFERRED_SIZE, 30, javax.swing.GroupLayout.PREFERRED_SIZE))
                                .addGap(18, 18, 18)
                                .addComponent(jButtonNewGame, javax.swing.GroupLayout.PREFERRED_SIZE, 36, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addGap(14, 14, 14)
                                .addComponent(jButtonRestart, javax.swing.GroupLayout.PREFERRED_SIZE, 36, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                                .addComponent(jButtonHint, javax.swing.GroupLayout.PREFERRED_SIZE, 36, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                                .addComponent(jButtonMistakes, javax.swing.GroupLayout.PREFERRED_SIZE, 36, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                                .addComponent(jButtonGiveUp, javax.swing.GroupLayout.PREFERRED_SIZE, 36, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                                .addComponent(jButtonClientGame, javax.swing.GroupLayout.PREFERRED_SIZE, 36, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                                .addComponent(jButtonSolve, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)))))
                .addContainerGap(16, Short.MAX_VALUE))
        );

        jMenu3.setText("File");

        jMenuItem1.setAccelerator(javax.swing.KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_S, java.awt.event.InputEvent.CTRL_MASK));
        jMenuItem1.setLabel("Save");
        jMenuItem1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMenuItem1ActionPerformed(evt);
            }
        });
        jMenu3.add(jMenuItem1);

        jMenuItem2.setAccelerator(javax.swing.KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_O, java.awt.event.InputEvent.CTRL_MASK));
        jMenuItem2.setLabel("Open");
        jMenuItem2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMenuItem2ActionPerformed(evt);
            }
        });
        jMenu3.add(jMenuItem2);
        jMenu3.add(jSeparator2);

        jMenuItem4.setAccelerator(javax.swing.KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_E, java.awt.event.InputEvent.SHIFT_MASK | java.awt.event.InputEvent.CTRL_MASK));
        jMenuItem4.setLabel("Exit");
        jMenuItem4.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMenuItem4ActionPerformed(evt);
            }
        });
        jMenu3.add(jMenuItem4);
        jMenuItem4.getAccessibleContext().setAccessibleName("Exit   ");

        jMenuBar1.add(jMenu3);

        jMenu4.setText("Game");

        jMenuItem18.setAccelerator(javax.swing.KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_N, java.awt.event.InputEvent.CTRL_MASK));
        jMenuItem18.setText("New Game");
        jMenuItem18.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMenuItem18ActionPerformed(evt);
            }
        });
        jMenu4.add(jMenuItem18);

        jMenuItem19.setAccelerator(javax.swing.KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_R, java.awt.event.InputEvent.CTRL_MASK));
        jMenuItem19.setText("Restart");
        jMenuItem19.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMenuItem19ActionPerformed(evt);
            }
        });
        jMenu4.add(jMenuItem19);

        jMenuItem20.setAccelerator(javax.swing.KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_H, java.awt.event.InputEvent.CTRL_MASK));
        jMenuItem20.setText("Hint");
        jMenuItem20.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMenuItem20ActionPerformed(evt);
            }
        });
        jMenu4.add(jMenuItem20);

        jMenuItem24.setAccelerator(javax.swing.KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_F, java.awt.event.InputEvent.CTRL_MASK));
        jMenuItem24.setText("Fix");
        jMenuItem24.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMenuItem24ActionPerformed(evt);
            }
        });
        jMenu4.add(jMenuItem24);

        jMenuItem21.setAccelerator(javax.swing.KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_G, java.awt.event.InputEvent.CTRL_MASK));
        jMenuItem21.setText("Give Up");
        jMenuItem21.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMenuItem21ActionPerformed(evt);
            }
        });
        jMenu4.add(jMenuItem21);

        jMenuItem22.setAccelerator(javax.swing.KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_M, java.awt.event.InputEvent.CTRL_MASK));
        jMenuItem22.setText("My Game");
        jMenuItem22.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMenuItem22ActionPerformed(evt);
            }
        });
        jMenu4.add(jMenuItem22);

        jMenuItem23.setAccelerator(javax.swing.KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_L, java.awt.event.InputEvent.CTRL_MASK));
        jMenuItem23.setText("Solve");
        jMenuItem23.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMenuItem23ActionPerformed(evt);
            }
        });
        jMenu4.add(jMenuItem23);

        jMenuBar1.add(jMenu4);

        jMenu5.setText("Color");

        jMenu1.setText("Background");

        jMenuItem11.setText("Red");
        jMenuItem11.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMenuItem11ActionPerformed(evt);
            }
        });
        jMenu1.add(jMenuItem11);

        jMenuItem5.setText("Orange");
        jMenuItem5.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMenuItem5ActionPerformed(evt);
            }
        });
        jMenu1.add(jMenuItem5);

        jMenuItem9.setText("Yellow");
        jMenuItem9.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMenuItem9ActionPerformed(evt);
            }
        });
        jMenu1.add(jMenuItem9);

        jMenuItem10.setText("Green");
        jMenuItem10.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMenuItem10ActionPerformed(evt);
            }
        });
        jMenu1.add(jMenuItem10);

        jMenuItem12.setText("Blue");
        jMenuItem12.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMenuItem12ActionPerformed(evt);
            }
        });
        jMenu1.add(jMenuItem12);

        jMenuItem3.setText("Silver");
        jMenuItem3.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMenuItem3ActionPerformed(evt);
            }
        });
        jMenu1.add(jMenuItem3);

        jMenuItem16.setText("Grey");
        jMenuItem16.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMenuItem16ActionPerformed(evt);
            }
        });
        jMenu1.add(jMenuItem16);

        jMenu5.add(jMenu1);

        jMenu2.setText("Borders");

        jMenuItem6.setText("Red");
        jMenuItem6.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMenuItem6ActionPerformed(evt);
            }
        });
        jMenu2.add(jMenuItem6);

        jMenuItem7.setText("Orange");
        jMenuItem7.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMenuItem7ActionPerformed(evt);
            }
        });
        jMenu2.add(jMenuItem7);

        jMenuItem8.setText("Yellow");
        jMenuItem8.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMenuItem8ActionPerformed(evt);
            }
        });
        jMenu2.add(jMenuItem8);

        jMenuItem13.setText("Green");
        jMenuItem13.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMenuItem13ActionPerformed(evt);
            }
        });
        jMenu2.add(jMenuItem13);

        jMenuItem14.setText("Blue");
        jMenuItem14.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMenuItem14ActionPerformed(evt);
            }
        });
        jMenu2.add(jMenuItem14);

        jMenuItem15.setText("Silver");
        jMenuItem15.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMenuItem15ActionPerformed(evt);
            }
        });
        jMenu2.add(jMenuItem15);

        jMenuItem17.setText("Grey");
        jMenuItem17.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMenuItem17ActionPerformed(evt);
            }
        });
        jMenu2.add(jMenuItem17);

        jMenu5.add(jMenu2);

        jMenuBar1.add(jMenu5);

        setJMenuBar(jMenuBar1);

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(jPanelMain, javax.swing.GroupLayout.DEFAULT_SIZE, 699, Short.MAX_VALUE)
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(jPanelMain, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.PREFERRED_SIZE, 513, javax.swing.GroupLayout.PREFERRED_SIZE)
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void jMenuItem1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jMenuItem1ActionPerformed
        if (clientGameActive == false) {
            saveGame = true;
            saveLoadActive = true;
            saveLoadForm.setVisible(true);
        }
    }//GEN-LAST:event_jMenuItem1ActionPerformed

    private void formWindowOpened(java.awt.event.WindowEvent evt) {//GEN-FIRST:event_formWindowOpened
        try {
            engine.newGame(difficulty + 1);
            fillCells();
        } catch (BadIndex i) {
            System.err.println("Bad index.");
        }
    }//GEN-LAST:event_formWindowOpened

    private void formWindowActivated(java.awt.event.WindowEvent evt) {//GEN-FIRST:event_formWindowActivated
    }//GEN-LAST:event_formWindowActivated

    private void jMenuItem4ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jMenuItem4ActionPerformed
        this.dispose();
    }//GEN-LAST:event_jMenuItem4ActionPerformed

    private void jMenuItem2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jMenuItem2ActionPerformed
        if (clientGameActive == false) {
            saveGame = false;
            saveLoadActive = true;
            saveLoadForm.setVisible(true);
        }
    }//GEN-LAST:event_jMenuItem2ActionPerformed

    private void changeBackgroundColor(java.awt.Color backgroundColor) {
        jPanelMain.setBackground(backgroundColor);
        jTextFieldNumberOfHints.setBackground(backgroundColor);
    }

    private void changePanelColor(java.awt.Color panelColor) {
        jPanel4.setBackground(panelColor);
        jPanel5.setBackground(panelColor);
        jPanel7.setBackground(panelColor);
        jPanel8.setBackground(panelColor);
        jPanel9.setBackground(panelColor);
        jPanel10.setBackground(panelColor);
        jPanel11.setBackground(panelColor);
        jPanel12.setBackground(panelColor);
        jPanel13.setBackground(panelColor);
        jPanel14.setBackground(panelColor);
        jPanel15.setBackground(panelColor);
        jPanel16.setBackground(panelColor);
    }

    private void jMenuItem9ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jMenuItem9ActionPerformed
        changeBackgroundColor(Color.yellow);
    }//GEN-LAST:event_jMenuItem9ActionPerformed

    private void jMenuItem10ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jMenuItem10ActionPerformed
        changeBackgroundColor(Color.green);
    }//GEN-LAST:event_jMenuItem10ActionPerformed

    private void jMenuItem12ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jMenuItem12ActionPerformed
        changeBackgroundColor(Color.cyan);
    }//GEN-LAST:event_jMenuItem12ActionPerformed

    private void jMenuItem11ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jMenuItem11ActionPerformed
        changeBackgroundColor(Color.pink);
    }//GEN-LAST:event_jMenuItem11ActionPerformed

    private void jMenuItem3ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jMenuItem3ActionPerformed
        changeBackgroundColor(Color.lightGray);
    }//GEN-LAST:event_jMenuItem3ActionPerformed

    private void jMenuItem5ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jMenuItem5ActionPerformed
        changeBackgroundColor(Color.orange);
    }//GEN-LAST:event_jMenuItem5ActionPerformed

    private void jMenuItem6ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jMenuItem6ActionPerformed
        changePanelColor(Color.pink);
    }//GEN-LAST:event_jMenuItem6ActionPerformed

    private void jMenuItem7ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jMenuItem7ActionPerformed
        changePanelColor(Color.orange);
    }//GEN-LAST:event_jMenuItem7ActionPerformed

    private void jMenuItem8ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jMenuItem8ActionPerformed
        changePanelColor(Color.yellow);
    }//GEN-LAST:event_jMenuItem8ActionPerformed

    private void jMenuItem13ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jMenuItem13ActionPerformed
        changePanelColor(Color.green);
    }//GEN-LAST:event_jMenuItem13ActionPerformed

    private void jMenuItem14ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jMenuItem14ActionPerformed
        changePanelColor(Color.cyan);
    }//GEN-LAST:event_jMenuItem14ActionPerformed

    private void jMenuItem15ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jMenuItem15ActionPerformed
        changePanelColor(Color.lightGray);
    }//GEN-LAST:event_jMenuItem15ActionPerformed

    private void jMenuItem16ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jMenuItem16ActionPerformed
        changeBackgroundColor(Color.gray);
    }//GEN-LAST:event_jMenuItem16ActionPerformed

    private void jMenuItem17ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jMenuItem17ActionPerformed
        changePanelColor(Color.gray);
    }//GEN-LAST:event_jMenuItem17ActionPerformed

    private void jMenuItem18ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jMenuItem18ActionPerformed
        jButtonNewGame.doClick();
    }//GEN-LAST:event_jMenuItem18ActionPerformed

    private void jMenuItem19ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jMenuItem19ActionPerformed
        if (jButtonRestart.isEnabled()) {
            jButtonRestart.doClick();
        }
    }//GEN-LAST:event_jMenuItem19ActionPerformed

    private void jMenuItem20ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jMenuItem20ActionPerformed
        if (jButtonHint.isEnabled()) {
            jButtonHint.doClick();
        }
    }//GEN-LAST:event_jMenuItem20ActionPerformed

    private void jMenuItem21ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jMenuItem21ActionPerformed
        if (jButtonGiveUp.isEnabled()) {
            jButtonGiveUp.doClick();
        }
    }//GEN-LAST:event_jMenuItem21ActionPerformed

    private void jMenuItem22ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jMenuItem22ActionPerformed
        if (jButtonClientGame.isEnabled()) {
            jButtonClientGame.doClick();
        }
    }//GEN-LAST:event_jMenuItem22ActionPerformed

    private void jMenuItem23ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jMenuItem23ActionPerformed
        if (jButtonSolve.isEnabled()) {
            jButtonSolve.doClick();
        }
    }//GEN-LAST:event_jMenuItem23ActionPerformed

    private void jButtonMistakesActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButtonMistakesActionPerformed
        ++numberOfHints;
        jTextFieldNumberOfHints.setText(String.valueOf(numberOfHints));
        int n = fieldSize;
        for (int i = 0; i < fieldSize; ++i) {
            for (int j = 0; j < fieldSize; ++j) {
                try {
                    if (!engine.isFilled(i + 1, j + 1)) {
                        if (!cells[i * n + j].value.getText().equals("")
                            && !cells[i * n + j].value.getText().equals(String.valueOf(engine.get(i + 1, j + 1)))) {
                            cells[i * n + j].value.setText("");
                            --numberOfFilledCells;
                            jProgressBarGameProgress.setValue(jProgressBarGameProgress.getValue() - 1);
                        }
                    }
                } catch (BadIndex ex) {
                    Logger.getLogger(MainWindow.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
        }
    }//GEN-LAST:event_jButtonMistakesActionPerformed

    private void jButtonHintActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButtonHintActionPerformed
        if (numbersTableActive || saveLoadActive) {
            return;
        }
        if (hintActive == true) {
            hintActive = false;
            jButtonHint.setBackground(hintButtonColor);
        } else {
            hintActive = true;
            jButtonHint.setBackground(Color.yellow);
        }
    }//GEN-LAST:event_jButtonHintActionPerformed

    private void jButtonRestartActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButtonRestartActionPerformed
        if (numbersTableActive || saveLoadActive) {
            return;
        }
        numberOfFilledCells = 0;
        numberOfHints = 0;
        hintActive = false;
        jTextFieldNumberOfHints.setText(String.valueOf(numberOfHints));
        jProgressBarGameProgress.setValue(engine.numberOfFilledCells());
        jButtonRestart.setEnabled(true);
        jButtonHint.setEnabled(true);
        jButtonHint.setBackground(hintButtonColor);
        jButtonMistakes.setEnabled(true);
        jButtonGiveUp.setEnabled(true);
        jButtonSolve.setEnabled(false);
        try {
            fillCells();
        } catch (BadIndex i) {
            System.err.println("Bad index.");
        }
    }//GEN-LAST:event_jButtonRestartActionPerformed

    private void jButtonGiveUpActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButtonGiveUpActionPerformed
        if (numbersTableActive || saveLoadActive) {
            return;
        }
        int n = fieldSize;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (cells[i * n + j].value.isEnabled() == true) {
                    try {
                        cells[i * n + j].value.setText(String.valueOf(engine.get(i + 1, j + 1)));
                    } catch (BadIndex bi) {
                        System.err.println("Bad index.");
                    }
                    cells[i * n + j].filled = true;
                    if (cells[i * n + j].value.getBackground().equals(Color.white)) {
                        cells[i * n + j].value.setBackground(Color.pink);
                    }
                }
            }
        }
        jButtonHint.setEnabled(false);
        jButtonHint.setBackground(hintButtonColor);
        jButtonMistakes.setEnabled(false);
        jButtonGiveUp.setEnabled(false);
        jProgressBarGameProgress.setValue(jProgressBarGameProgress.getMaximum());
    }//GEN-LAST:event_jButtonGiveUpActionPerformed

    private void jButtonSolveActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButtonSolveActionPerformed
        if (numbersTableActive || saveLoadActive) {
            return;
        }
        final int n = fieldSize;
        int[][] arr = new int[n][n];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (cells[i * n + j].value.getText().equals("")) {
                    arr[i][j] = 0;
                } else {
                    arr[i][j] = Integer.valueOf(cells[i * n + j].value.getText());
                }
            }
        }
        try {
            engine.solveTask(arr);
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    arr[i][j] = engine.get(i + 1, j + 1);
                }
            }
            if (engine.solutions() == 1) {
                for (int i = 0; i < n; ++i) {
                    for (int j = 0; j < n; ++j) {
                        cells[i * n + j].filled = true;
                        if (!cells[i * n + j].value.getText().equals("")) {
                            cells[i * n + j].value.setEnabled(false);
                            cells[i * n + j].value.setBackground(Color.white);
                        } else {
                            cells[i * n + j].value.setText(String.valueOf(engine.get(i + 1, j + 1)));
                            cells[i * n + j].value.setBackground(Color.cyan);
                        }
                    }
                }
                jProgressBarGameProgress.setValue(jProgressBarGameProgress.getMaximum());
                jButtonSolve.setEnabled(false);
            }
        } catch (BadIndex bi) {
            System.err.println("Bad index.");
        }
    }//GEN-LAST:event_jButtonSolveActionPerformed

    private void jButtonClientGameActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButtonClientGameActionPerformed
        if (numbersTableActive || saveLoadActive) {
            return;
        }
        numberOfFilledCells = 0;
        numberOfHints = 0;
        hintActive = false;
        clientGameActive = true;
        jTextFieldNumberOfHints.setText(String.valueOf(numberOfHints));
        jProgressBarGameProgress.setValue(jProgressBarGameProgress.getMinimum());
        jProgressBarGameProgress.setForeground(Color.GREEN);
        jButtonRestart.setEnabled(false);
        jButtonHint.setEnabled(false);
        jButtonHint.setBackground(hintButtonColor);
        jButtonMistakes.setEnabled(false);
        jButtonGiveUp.setEnabled(false);
        jButtonSolve.setEnabled(true);
        final int n = fieldSize;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cells[i * n + j].value.setText("");
                cells[i * n + j].filled = false;
                cells[i * n + j].value.setEnabled(true);
                cells[i * n + j].value.setBackground(Color.white);
            }
        }
    }//GEN-LAST:event_jButtonClientGameActionPerformed

    private void jComboBoxDifficultyActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jComboBoxDifficultyActionPerformed
        difficulty = jComboBoxDifficulty.getSelectedIndex();
        switch (difficulty) {
            case 0:
            jComboBoxDifficulty.setBackground(Color.lightGray);
            break;
            case 1:
            jComboBoxDifficulty.setBackground(Color.green);
            break;
            case 2:
            jComboBoxDifficulty.setBackground(Color.yellow);
            break;
            case 3:
            jComboBoxDifficulty.setBackground(Color.orange);
            break;
            case 4:
            jComboBoxDifficulty.setBackground(Color.red);
            break;
        }
    }//GEN-LAST:event_jComboBoxDifficultyActionPerformed

    private void jButtonNewGameActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButtonNewGameActionPerformed
        if (numbersTableActive || saveLoadActive) {
            return;
        }
        numberOfFilledCells = 0;
        numberOfHints = 0;
        hintActive = false;
        clientGameActive = false;
        jTextFieldNumberOfHints.setText(String.valueOf(numberOfHints));
        jButtonRestart.setEnabled(true);
        jButtonHint.setEnabled(true);
        jButtonHint.setBackground(hintButtonColor);
        jButtonMistakes.setEnabled(true);
        jButtonGiveUp.setEnabled(true);
        jButtonSolve.setEnabled(false);
        try {
            engine.newGame(difficulty);
            fillCells();
        } catch (BadIndex i) {
            System.err.println("Bad index.");
        }
        jProgressBarGameProgress.setValue(engine.numberOfFilledCells());
        jProgressBarGameProgress.setForeground(Color.orange);
    }//GEN-LAST:event_jButtonNewGameActionPerformed

    private void jTextField81MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField81MouseClicked
        actionForMouseClick(81);
    }//GEN-LAST:event_jTextField81MouseClicked

    private void jTextField80MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField80MouseClicked
        actionForMouseClick(80);
    }//GEN-LAST:event_jTextField80MouseClicked

    private void jTextField79MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField79MouseClicked
        actionForMouseClick(79);
    }//GEN-LAST:event_jTextField79MouseClicked

    private void jTextField78MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField78MouseClicked
        actionForMouseClick(78);
    }//GEN-LAST:event_jTextField78MouseClicked

    private void jTextField77MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField77MouseClicked
        actionForMouseClick(77);
    }//GEN-LAST:event_jTextField77MouseClicked

    private void jTextField76MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField76MouseClicked
        actionForMouseClick(76);
    }//GEN-LAST:event_jTextField76MouseClicked

    private void jTextField75MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField75MouseClicked
        actionForMouseClick(75);
    }//GEN-LAST:event_jTextField75MouseClicked

    private void jTextField74MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField74MouseClicked
        actionForMouseClick(74);
    }//GEN-LAST:event_jTextField74MouseClicked

    private void jTextField73MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField73MouseClicked
        actionForMouseClick(73);
    }//GEN-LAST:event_jTextField73MouseClicked

    private void jTextField72MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField72MouseClicked
        actionForMouseClick(72);
    }//GEN-LAST:event_jTextField72MouseClicked

    private void jTextField71MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField71MouseClicked
        actionForMouseClick(71);
    }//GEN-LAST:event_jTextField71MouseClicked

    private void jTextField70MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField70MouseClicked
        actionForMouseClick(70);
    }//GEN-LAST:event_jTextField70MouseClicked

    private void jTextField69MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField69MouseClicked
        actionForMouseClick(69);
    }//GEN-LAST:event_jTextField69MouseClicked

    private void jTextField68MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField68MouseClicked
        actionForMouseClick(68);
    }//GEN-LAST:event_jTextField68MouseClicked

    private void jTextField67MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField67MouseClicked
        actionForMouseClick(67);
    }//GEN-LAST:event_jTextField67MouseClicked

    private void jTextField66MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField66MouseClicked
        actionForMouseClick(66);
    }//GEN-LAST:event_jTextField66MouseClicked

    private void jTextField65MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField65MouseClicked
        actionForMouseClick(65);
    }//GEN-LAST:event_jTextField65MouseClicked

    private void jTextField64MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField64MouseClicked
        actionForMouseClick(64);
    }//GEN-LAST:event_jTextField64MouseClicked

    private void jTextField63MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField63MouseClicked
        actionForMouseClick(63);
    }//GEN-LAST:event_jTextField63MouseClicked

    private void jTextField62MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField62MouseClicked
        actionForMouseClick(62);
    }//GEN-LAST:event_jTextField62MouseClicked

    private void jTextField61MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField61MouseClicked
        actionForMouseClick(61);
    }//GEN-LAST:event_jTextField61MouseClicked

    private void jTextField60MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField60MouseClicked
        actionForMouseClick(60);
    }//GEN-LAST:event_jTextField60MouseClicked

    private void jTextField59MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField59MouseClicked
        actionForMouseClick(59);
    }//GEN-LAST:event_jTextField59MouseClicked

    private void jTextField58MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField58MouseClicked
        actionForMouseClick(58);
    }//GEN-LAST:event_jTextField58MouseClicked

    private void jTextField57MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField57MouseClicked
        actionForMouseClick(57);
    }//GEN-LAST:event_jTextField57MouseClicked

    private void jTextField56MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField56MouseClicked
        actionForMouseClick(56);
    }//GEN-LAST:event_jTextField56MouseClicked

    private void jTextField55MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField55MouseClicked
        actionForMouseClick(55);
    }//GEN-LAST:event_jTextField55MouseClicked

    private void jTextField54MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField54MouseClicked
        actionForMouseClick(54);
    }//GEN-LAST:event_jTextField54MouseClicked

    private void jTextField53MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField53MouseClicked
        actionForMouseClick(53);
    }//GEN-LAST:event_jTextField53MouseClicked

    private void jTextField52MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField52MouseClicked
        actionForMouseClick(52);
    }//GEN-LAST:event_jTextField52MouseClicked

    private void jTextField51MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField51MouseClicked
        actionForMouseClick(51);
    }//GEN-LAST:event_jTextField51MouseClicked

    private void jTextField50MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField50MouseClicked
        actionForMouseClick(50);
    }//GEN-LAST:event_jTextField50MouseClicked

    private void jTextField49MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField49MouseClicked
        actionForMouseClick(49);
    }//GEN-LAST:event_jTextField49MouseClicked

    private void jTextField48MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField48MouseClicked
        actionForMouseClick(48);
    }//GEN-LAST:event_jTextField48MouseClicked

    private void jTextField47MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField47MouseClicked
        actionForMouseClick(47);
    }//GEN-LAST:event_jTextField47MouseClicked

    private void jTextField46MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField46MouseClicked
        actionForMouseClick(46);
    }//GEN-LAST:event_jTextField46MouseClicked

    private void jTextField45MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField45MouseClicked
        actionForMouseClick(45);
    }//GEN-LAST:event_jTextField45MouseClicked

    private void jTextField44MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField44MouseClicked
        actionForMouseClick(44);
    }//GEN-LAST:event_jTextField44MouseClicked

    private void jTextField43MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField43MouseClicked
        actionForMouseClick(43);
    }//GEN-LAST:event_jTextField43MouseClicked

    private void jTextField42MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField42MouseClicked
        actionForMouseClick(42);
    }//GEN-LAST:event_jTextField42MouseClicked

    private void jTextField41MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField41MouseClicked
        actionForMouseClick(41);
    }//GEN-LAST:event_jTextField41MouseClicked

    private void jTextField40MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField40MouseClicked
        actionForMouseClick(40);
    }//GEN-LAST:event_jTextField40MouseClicked

    private void jTextField39MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField39MouseClicked
        actionForMouseClick(39);
    }//GEN-LAST:event_jTextField39MouseClicked

    private void jTextField38MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField38MouseClicked
        actionForMouseClick(38);
    }//GEN-LAST:event_jTextField38MouseClicked

    private void jTextField37MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField37MouseClicked
        actionForMouseClick(37);
    }//GEN-LAST:event_jTextField37MouseClicked

    private void jTextField36MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField36MouseClicked
        actionForMouseClick(36);
    }//GEN-LAST:event_jTextField36MouseClicked

    private void jTextField35MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField35MouseClicked
        actionForMouseClick(35);
    }//GEN-LAST:event_jTextField35MouseClicked

    private void jTextField34MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField34MouseClicked
        actionForMouseClick(34);
    }//GEN-LAST:event_jTextField34MouseClicked

    private void jTextField33MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField33MouseClicked
        actionForMouseClick(33);
    }//GEN-LAST:event_jTextField33MouseClicked

    private void jTextField32MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField32MouseClicked
        actionForMouseClick(32);
    }//GEN-LAST:event_jTextField32MouseClicked

    private void jTextField31MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField31MouseClicked
        actionForMouseClick(31);
    }//GEN-LAST:event_jTextField31MouseClicked

    private void jTextField30MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField30MouseClicked
        actionForMouseClick(30);
    }//GEN-LAST:event_jTextField30MouseClicked

    private void jTextField29MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField29MouseClicked
        actionForMouseClick(29);
    }//GEN-LAST:event_jTextField29MouseClicked

    private void jTextField28MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField28MouseClicked
        actionForMouseClick(28);
    }//GEN-LAST:event_jTextField28MouseClicked

    private void jTextField27MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField27MouseClicked
        actionForMouseClick(27);
    }//GEN-LAST:event_jTextField27MouseClicked

    private void jTextField26MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField26MouseClicked
        actionForMouseClick(26);
    }//GEN-LAST:event_jTextField26MouseClicked

    private void jTextField25MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField25MouseClicked
        actionForMouseClick(25);
    }//GEN-LAST:event_jTextField25MouseClicked

    private void jTextField24MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField24MouseClicked
        actionForMouseClick(24);
    }//GEN-LAST:event_jTextField24MouseClicked

    private void jTextField23MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField23MouseClicked
        actionForMouseClick(23);
    }//GEN-LAST:event_jTextField23MouseClicked

    private void jTextField22MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField22MouseClicked
        actionForMouseClick(22);
    }//GEN-LAST:event_jTextField22MouseClicked

    private void jTextField21MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField21MouseClicked
        actionForMouseClick(21);
    }//GEN-LAST:event_jTextField21MouseClicked

    private void jTextField20MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField20MouseClicked
        actionForMouseClick(20);
    }//GEN-LAST:event_jTextField20MouseClicked

    private void jTextField19MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField19MouseClicked
        actionForMouseClick(19);
    }//GEN-LAST:event_jTextField19MouseClicked

    private void jTextField18MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField18MouseClicked
        actionForMouseClick(18);
    }//GEN-LAST:event_jTextField18MouseClicked

    private void jTextField17MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField17MouseClicked
        actionForMouseClick(17);
    }//GEN-LAST:event_jTextField17MouseClicked

    private void jTextField16ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jTextField16ActionPerformed

    }//GEN-LAST:event_jTextField16ActionPerformed

    private void jTextField16MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField16MouseClicked
        actionForMouseClick(16);
    }//GEN-LAST:event_jTextField16MouseClicked

    private void jTextField15MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField15MouseClicked
        actionForMouseClick(15);
    }//GEN-LAST:event_jTextField15MouseClicked

    private void jTextField14MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField14MouseClicked
        actionForMouseClick(14);
    }//GEN-LAST:event_jTextField14MouseClicked

    private void jTextField13MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField13MouseClicked
        actionForMouseClick(13);
    }//GEN-LAST:event_jTextField13MouseClicked

    private void jTextField12MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField12MouseClicked
        actionForMouseClick(12);
    }//GEN-LAST:event_jTextField12MouseClicked

    private void jTextField11MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField11MouseClicked
        actionForMouseClick(11);
    }//GEN-LAST:event_jTextField11MouseClicked

    private void jTextField10MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField10MouseClicked
        actionForMouseClick(10);
    }//GEN-LAST:event_jTextField10MouseClicked

    private void jTextField9MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField9MouseClicked
        actionForMouseClick(9);
    }//GEN-LAST:event_jTextField9MouseClicked

    private void jTextField8MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField8MouseClicked
        actionForMouseClick(8);
    }//GEN-LAST:event_jTextField8MouseClicked

    private void jTextField7MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField7MouseClicked
        actionForMouseClick(7);
    }//GEN-LAST:event_jTextField7MouseClicked

    private void jTextField6MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField6MouseClicked
        actionForMouseClick(6);
    }//GEN-LAST:event_jTextField6MouseClicked

    private void jTextField5MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField5MouseClicked
        actionForMouseClick(5);
    }//GEN-LAST:event_jTextField5MouseClicked

    private void jTextField4MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField4MouseClicked
        actionForMouseClick(4);
    }//GEN-LAST:event_jTextField4MouseClicked

    private void jTextField3MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField3MouseClicked
        actionForMouseClick(3);
    }//GEN-LAST:event_jTextField3MouseClicked

    private void jTextField2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jTextField2ActionPerformed

    }//GEN-LAST:event_jTextField2ActionPerformed

    private void jTextField2MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField2MouseClicked
        actionForMouseClick(2);
    }//GEN-LAST:event_jTextField2MouseClicked

    private void jTextField1KeyReleased(java.awt.event.KeyEvent evt) {//GEN-FIRST:event_jTextField1KeyReleased

    }//GEN-LAST:event_jTextField1KeyReleased

    private void jTextField1KeyPressed(java.awt.event.KeyEvent evt) {//GEN-FIRST:event_jTextField1KeyPressed

    }//GEN-LAST:event_jTextField1KeyPressed

    private void jTextField1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jTextField1ActionPerformed

    }//GEN-LAST:event_jTextField1ActionPerformed

    private void jTextField1MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextField1MouseClicked
        actionForMouseClick(1);
    }//GEN-LAST:event_jTextField1MouseClicked

    private void jMenuItem24ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jMenuItem24ActionPerformed
        if (jButtonMistakes.isEnabled()) {
            jButtonMistakes.doClick();
        }
    }//GEN-LAST:event_jMenuItem24ActionPerformed

    private void actionForMouseClick(final int numberOfCell) {
        if (!numbersTableActive && !saveLoadActive) {
            numberOfActiveCell = numberOfCell - 1;
            if (hintActive == true && cells[numberOfActiveCell].value.isEnabled()) {
                jButtonHint.setBackground(hintButtonColor);
                try {
                    if (cells[numberOfActiveCell].value.getText().equals("")) {
                        ++numberOfFilledCells;
                        jProgressBarGameProgress.setValue(jProgressBarGameProgress.getValue() + 1);
                    }
                    cells[numberOfActiveCell].filled = true;
                    if (numberOfCell == 81) {
                        cells[numberOfActiveCell].value.setText(String.valueOf(engine.get(fieldSize, fieldSize)));
                    } else {
                        cells[numberOfActiveCell].value.setText(String.valueOf(numberOfCell % fieldSize != 0
                                ? (engine.get(numberOfCell / fieldSize + 1, numberOfCell % fieldSize))
                                : (engine.get(numberOfCell / fieldSize, fieldSize))));
                    }
                    cells[numberOfActiveCell].value.setBackground(Color.yellow);
                    ++numberOfHints;
                    hintActive = false;
                    jTextFieldNumberOfHints.setText(String.valueOf(numberOfHints));
                    if (numberOfFilledCells >= 81) {
                        if (isFilledCorrectly()) {
                            activateResult();
                        }
                    }
                } catch (BadIndex bi) {
                    System.err.println("Bad index.");
                }
            } else if (!cells[numberOfActiveCell].filled) {
                numbersTable.setVisible(true);
                numbersTableActive = true;
            }
        }
    }

    private void activateResult() {
        int n = fieldSize;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cells[i * n + j].filled = true;
                if (cells[i * n + j].value.getBackground().equals(Color.white)) {
                    cells[i * n + j].value.setBackground(Color.green);
                }
            }
        }
        jButtonHint.setEnabled(false);
        jButtonMistakes.setEnabled(false);
        jButtonGiveUp.setEnabled(false);
    }

    private void initCellArray() {
        cells = new OverloadedCell[numberOfCells];
        for (int i = 0; i < numberOfCells; ++i) {
            cells[i] = new OverloadedCell();
            cells[i].value = new javax.swing.JTextField();
            cells[i].filled = false;
        }
        cells[0].value = jTextField1;
        cells[1].value = jTextField2;
        cells[2].value = jTextField3;
        cells[3].value = jTextField4;
        cells[4].value = jTextField5;
        cells[5].value = jTextField6;
        cells[6].value = jTextField7;
        cells[7].value = jTextField8;
        cells[8].value = jTextField9;
        cells[9].value = jTextField10;
        cells[10].value = jTextField11;
        cells[11].value = jTextField12;
        cells[12].value = jTextField13;
        cells[13].value = jTextField14;
        cells[14].value = jTextField15;
        cells[15].value = jTextField16;
        cells[16].value = jTextField17;
        cells[17].value = jTextField18;
        cells[18].value = jTextField19;
        cells[19].value = jTextField20;
        cells[20].value = jTextField21;
        cells[21].value = jTextField22;
        cells[22].value = jTextField23;
        cells[23].value = jTextField24;
        cells[24].value = jTextField25;
        cells[25].value = jTextField26;
        cells[26].value = jTextField27;
        cells[27].value = jTextField28;
        cells[28].value = jTextField29;
        cells[29].value = jTextField30;
        cells[30].value = jTextField31;
        cells[31].value = jTextField32;
        cells[32].value = jTextField33;
        cells[33].value = jTextField34;
        cells[34].value = jTextField35;
        cells[35].value = jTextField36;
        cells[36].value = jTextField37;
        cells[37].value = jTextField38;
        cells[38].value = jTextField39;
        cells[39].value = jTextField40;
        cells[40].value = jTextField41;
        cells[41].value = jTextField42;
        cells[42].value = jTextField43;
        cells[43].value = jTextField44;
        cells[44].value = jTextField45;
        cells[45].value = jTextField46;
        cells[46].value = jTextField47;
        cells[47].value = jTextField48;
        cells[48].value = jTextField49;
        cells[49].value = jTextField50;
        cells[50].value = jTextField51;
        cells[51].value = jTextField52;
        cells[52].value = jTextField53;
        cells[53].value = jTextField54;
        cells[54].value = jTextField55;
        cells[55].value = jTextField56;
        cells[56].value = jTextField57;
        cells[57].value = jTextField58;
        cells[58].value = jTextField59;
        cells[59].value = jTextField60;
        cells[60].value = jTextField61;
        cells[61].value = jTextField62;
        cells[62].value = jTextField63;
        cells[63].value = jTextField64;
        cells[64].value = jTextField65;
        cells[65].value = jTextField66;
        cells[66].value = jTextField67;
        cells[67].value = jTextField68;
        cells[68].value = jTextField69;
        cells[69].value = jTextField70;
        cells[70].value = jTextField71;
        cells[71].value = jTextField72;
        cells[72].value = jTextField73;
        cells[73].value = jTextField74;
        cells[74].value = jTextField75;
        cells[75].value = jTextField76;
        cells[76].value = jTextField77;
        cells[77].value = jTextField78;
        cells[78].value = jTextField79;
        cells[79].value = jTextField80;
        cells[80].value = jTextField81;
    }

    private void fillCells() throws BadIndex {
        final int n = fieldSize;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cells[i * n + j].value.setText(engine.isFilled(i + 1, j + 1) ? String.valueOf(engine.get(i + 1, j + 1)) : "");
                cells[i * n + j].filled = engine.isFilled(i + 1, j + 1);
                cells[i * n + j].value.setBackground(Color.white);
                if (cells[i * n + j].filled) {
                    cells[i * n + j].value.setEnabled(false);
                    cells[i * n + j].value.setBackground(Color.white);
                    ++numberOfFilledCells;
                } else {
                    cells[i * n + j].value.setEnabled(true);
                }
            }
        }
    }

    private boolean isFilledCorrectly() {
        final int n = fieldSize;
        try {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (!cells[i * n + j].value.getText().
                            equals(String.valueOf(engine.get(i + 1, j + 1)))) {
                        return false;
                    }
                }
            }
        } catch (BadIndex bi) {
            System.err.println("Bad index.");
        }
        return true;
    }

    public static void main(String args[]) {
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException | InstantiationException | IllegalAccessException | javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(MainWindow.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }

        java.awt.EventQueue.invokeLater(new Runnable() {
            @Override
            public void run() {
                MainWindow mainWindow = new MainWindow();
                mainWindow.setLocation(400, 100);
                mainWindow.setSize(705, 570);
                mainWindow.setResizable(false);
                mainWindow.setVisible(true);
            }
        });
    }
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton jButtonClientGame;
    private javax.swing.JButton jButtonGiveUp;
    private javax.swing.JButton jButtonHint;
    private javax.swing.JButton jButtonMistakes;
    private javax.swing.JButton jButtonNewGame;
    private javax.swing.JButton jButtonRestart;
    private javax.swing.JButton jButtonSolve;
    private javax.swing.JComboBox jComboBoxDifficulty;
    private javax.swing.JLabel jLabelHints;
    private javax.swing.JLabel jLabelProgress;
    private javax.swing.JMenu jMenu1;
    private javax.swing.JMenu jMenu2;
    private javax.swing.JMenu jMenu3;
    private javax.swing.JMenu jMenu4;
    private javax.swing.JMenu jMenu5;
    private javax.swing.JMenuBar jMenuBar1;
    private javax.swing.JMenuItem jMenuItem1;
    private javax.swing.JMenuItem jMenuItem10;
    private javax.swing.JMenuItem jMenuItem11;
    private javax.swing.JMenuItem jMenuItem12;
    private javax.swing.JMenuItem jMenuItem13;
    private javax.swing.JMenuItem jMenuItem14;
    private javax.swing.JMenuItem jMenuItem15;
    private javax.swing.JMenuItem jMenuItem16;
    private javax.swing.JMenuItem jMenuItem17;
    private javax.swing.JMenuItem jMenuItem18;
    private javax.swing.JMenuItem jMenuItem19;
    private javax.swing.JMenuItem jMenuItem2;
    private javax.swing.JMenuItem jMenuItem20;
    private javax.swing.JMenuItem jMenuItem21;
    private javax.swing.JMenuItem jMenuItem22;
    private javax.swing.JMenuItem jMenuItem23;
    private javax.swing.JMenuItem jMenuItem24;
    private javax.swing.JMenuItem jMenuItem3;
    private javax.swing.JMenuItem jMenuItem4;
    private javax.swing.JMenuItem jMenuItem5;
    private javax.swing.JMenuItem jMenuItem6;
    private javax.swing.JMenuItem jMenuItem7;
    private javax.swing.JMenuItem jMenuItem8;
    private javax.swing.JMenuItem jMenuItem9;
    private javax.swing.JPanel jPanel10;
    private javax.swing.JPanel jPanel11;
    private javax.swing.JPanel jPanel12;
    private javax.swing.JPanel jPanel13;
    private javax.swing.JPanel jPanel14;
    private javax.swing.JPanel jPanel15;
    private javax.swing.JPanel jPanel16;
    private javax.swing.JPanel jPanel4;
    private javax.swing.JPanel jPanel5;
    private javax.swing.JPanel jPanel7;
    private javax.swing.JPanel jPanel8;
    private javax.swing.JPanel jPanel9;
    private javax.swing.JPanel jPanelMain;
    private javax.swing.JProgressBar jProgressBarGameProgress;
    private javax.swing.JPopupMenu.Separator jSeparator2;
    private javax.swing.JTextField jTextField1;
    private javax.swing.JTextField jTextField10;
    private javax.swing.JTextField jTextField11;
    private javax.swing.JTextField jTextField12;
    private javax.swing.JTextField jTextField13;
    private javax.swing.JTextField jTextField14;
    private javax.swing.JTextField jTextField15;
    private javax.swing.JTextField jTextField16;
    private javax.swing.JTextField jTextField17;
    private javax.swing.JTextField jTextField18;
    private javax.swing.JTextField jTextField19;
    private javax.swing.JTextField jTextField2;
    private javax.swing.JTextField jTextField20;
    private javax.swing.JTextField jTextField21;
    private javax.swing.JTextField jTextField22;
    private javax.swing.JTextField jTextField23;
    private javax.swing.JTextField jTextField24;
    private javax.swing.JTextField jTextField25;
    private javax.swing.JTextField jTextField26;
    private javax.swing.JTextField jTextField27;
    private javax.swing.JTextField jTextField28;
    private javax.swing.JTextField jTextField29;
    private javax.swing.JTextField jTextField3;
    private javax.swing.JTextField jTextField30;
    private javax.swing.JTextField jTextField31;
    private javax.swing.JTextField jTextField32;
    private javax.swing.JTextField jTextField33;
    private javax.swing.JTextField jTextField34;
    private javax.swing.JTextField jTextField35;
    private javax.swing.JTextField jTextField36;
    private javax.swing.JTextField jTextField37;
    private javax.swing.JTextField jTextField38;
    private javax.swing.JTextField jTextField39;
    private javax.swing.JTextField jTextField4;
    private javax.swing.JTextField jTextField40;
    private javax.swing.JTextField jTextField41;
    private javax.swing.JTextField jTextField42;
    private javax.swing.JTextField jTextField43;
    private javax.swing.JTextField jTextField44;
    private javax.swing.JTextField jTextField45;
    private javax.swing.JTextField jTextField46;
    private javax.swing.JTextField jTextField47;
    private javax.swing.JTextField jTextField48;
    private javax.swing.JTextField jTextField49;
    private javax.swing.JTextField jTextField5;
    private javax.swing.JTextField jTextField50;
    private javax.swing.JTextField jTextField51;
    private javax.swing.JTextField jTextField52;
    private javax.swing.JTextField jTextField53;
    private javax.swing.JTextField jTextField54;
    private javax.swing.JTextField jTextField55;
    private javax.swing.JTextField jTextField56;
    private javax.swing.JTextField jTextField57;
    private javax.swing.JTextField jTextField58;
    private javax.swing.JTextField jTextField59;
    private javax.swing.JTextField jTextField6;
    private javax.swing.JTextField jTextField60;
    private javax.swing.JTextField jTextField61;
    private javax.swing.JTextField jTextField62;
    private javax.swing.JTextField jTextField63;
    private javax.swing.JTextField jTextField64;
    private javax.swing.JTextField jTextField65;
    private javax.swing.JTextField jTextField66;
    private javax.swing.JTextField jTextField67;
    private javax.swing.JTextField jTextField68;
    private javax.swing.JTextField jTextField69;
    private javax.swing.JTextField jTextField7;
    private javax.swing.JTextField jTextField70;
    private javax.swing.JTextField jTextField71;
    private javax.swing.JTextField jTextField72;
    private javax.swing.JTextField jTextField73;
    private javax.swing.JTextField jTextField74;
    private javax.swing.JTextField jTextField75;
    private javax.swing.JTextField jTextField76;
    private javax.swing.JTextField jTextField77;
    private javax.swing.JTextField jTextField78;
    private javax.swing.JTextField jTextField79;
    private javax.swing.JTextField jTextField8;
    private javax.swing.JTextField jTextField80;
    private javax.swing.JTextField jTextField81;
    private javax.swing.JTextField jTextField9;
    private javax.swing.JTextField jTextFieldNumberOfHints;
    // End of variables declaration//GEN-END:variables
}
