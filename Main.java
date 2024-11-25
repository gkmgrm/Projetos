package Projeto2;

import Projeto2.Encomendas.Encomendas;
import Projeto2.MeiosDeTransporte.MeioAereo;
import Projeto2.MeiosDeTransporte.MeioAquatico;
import Projeto2.MeiosDeTransporte.MeioTerrestre;
import Projeto2.MeiosDeTransporte.MeiosDeTransporte;
import Utils.InputValidation;

import java.util.Scanner;
import java.util.ArrayList;


/*
    Nome: Projeto 2

    Autores: Gonçalo Pimenta    24265
             Guilherme Miranda  24156

 */


public class Main {

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);
        Encomendas encomenda = new Encomendas();

        ArrayList<Encomendas>encomendas = new ArrayList<>();

        ArrayList<MeioTerrestre>meioTerrestres = new ArrayList<>();
        ArrayList<MeioTerrestre>copiaTerrestre = new ArrayList<>();

        ArrayList<MeioAquatico>meioAquaticos = new ArrayList<>();
        ArrayList<MeioAquatico>copiaAquatico = new ArrayList<>();

        ArrayList<MeioAereo>meioAereos = new ArrayList<>();
        ArrayList<MeioAereo>copiaAereo = new ArrayList<>();

        int option = -1, optionAdicionarT;

        while (option != 0){
            menu();
            option = InputValidation.validateIntBetween(sc, "Opção > ", 0, 5);  // verifica se a opção está dentro do intervalo
            boolean adicionarTransporte = false, removerTransporte = false, listarTransporte = false;    // verifica se o transporte foi adicionado, removido e listado

            switch (option){

                case 0:
                    System.out.println("Adeus!");
                    break;
                case 1:
                    System.out.println("Adicionar meio de transporte");
                    while (!adicionarTransporte){
                        adicionarTransporte();
                        optionAdicionarT = InputValidation.validateIntBetween(sc, "\nOpção > ", 0, 3);
                        switch (optionAdicionarT){
                            case 0:
                                adicionarTransporte = true; //  Flag para sair do ciclo Adicionar transporte
                                break;
                            case 1:
                                meioTerrestres.add(new MeioTerrestre(sc));  //  Adiciona um novo transporte terrestre ao arraylist
                                copiaTerrestre.addAll(meioTerrestres);      //  Faz uma cópia do original
                                adicionarTransporte = true;
                                break;
                            case 2:
                                meioAquaticos.add(new MeioAquatico(sc));    //  Adiciona um novo transporte aquático ao arraylist
                                copiaAquatico.addAll(meioAquaticos);        //  Faz uma cópia do original
                                adicionarTransporte = true;
                                break;
                            case 3:
                                meioAereos.add(new MeioAereo(sc));  //  Adiciona um novo transporte aéreo ao arraylist
                                copiaAereo.addAll(meioAereos);      //  Faz uma cópia do original
                                adicionarTransporte = true;
                                break;

                        }
                        System.out.println("\nTransporte adicionado!");

                    }
                    break;
                case 2:
                    while (!removerTransporte){
                        System.out.println("2 - Remover meio de transporte");
                        adicionarTransporte();

                        optionAdicionarT = InputValidation.validateIntBetween(sc, "\nOpção > ", 0, 3);
                        switch (optionAdicionarT){
                            case 0:
                                removerTransporte = true; //  Flag para sair do ciclo Remover transporte
                                break;
                            case 1:
                                //  removerTransporte é atualizada e sai do ciclo caso seja verdadeira, caso contrário continua no ciclo
                                removerTransporte = removerTerrestre(meioTerrestres, sc, removerTransporte);
                                break;
                            case 2:
                                removerTransporte = removerAquatico(meioAquaticos, sc, removerTransporte);
                                break;
                            case 3:
                                removerTransporte = removerAereo(meioAereos, sc, removerTransporte);
                                break;

                        }


                    }
                    break;
                case 3:

                    while (!listarTransporte) {
                        System.out.println("3 - Listar meios de transporte");
                        adicionarTransporte();
                        optionAdicionarT = InputValidation.validateIntBetween(sc, "\nOpção > ", 0, 3);
                        switch (optionAdicionarT) {
                            case 0:
                                listarTransporte = true; //  Flag para sair do ciclo listar transporte
                                break;
                            case 1:
                                listarTransportes(meioTerrestres);
                                listarTransporte = true;
                                break;
                            case 2:
                                listarTransportes(meioAquaticos);
                                listarTransporte = true;
                                break;
                            case 3:
                                listarTransportes(meioAereos);
                                listarTransporte = true;
                                break;
                        }
                    }
                    break;
                case 4:
                    System.out.println("4 - Transportar encomenda");
                    selecionaeTransporta(meioTerrestres, sc, encomendas, meioAquaticos, meioAereos);
                    break;
                case 5:
                    System.out.println("5 - Listar encomendas transportadas");
                    listarEncomendas(encomendas, copiaTerrestre, copiaAquatico, copiaAereo);
                    break;
            }


        }

        sc.close();
    }

    private static void menu(){ //Menu

        System.out.println("\n----- Menu -----");
        System.out.println("\t1 - Adicionar meio de transporte");
        System.out.println("\t2 - Remover meio de transporte");
        System.out.println("\t3 - Listar meio de transporte");
        System.out.println("\t4 - Transportar encomenda");
        System.out.println("\t5 - Listar encomendas transportadas");
        System.out.println("\t0 - Sair");
        System.out.println("---------------");

    }

    private static void adicionarTransporte(){  // Menu adicionar meio de transporte
        System.out.println();
        System.out.println("\t1 - Terrestre");
        System.out.println("\t2 - Aquático");
        System.out.println("\t3 - Aéreo");
        System.out.println("\t0 - Voltar");
    }

    private static void listarTransportes(ArrayList<? extends MeiosDeTransporte> meiosDeTransportes) {

        if (!meiosDeTransportes.isEmpty()) { // Verifica se existem transportes salvos no ArrayList
            System.out.println("\n----- Listagem Transportes -----");
            for (MeiosDeTransporte transporte : meiosDeTransportes)  // Percorre o arraylist de transportes
                System.out.println("\n" + transporte.toString());   //  Lista todas as informações dos meios adicionados
            System.out.println("\n--------------------------------\n");

        } else
            System.out.println("Sem transportes deste tipo adicionados!\n");

    }

    private static void listarEncomendas(ArrayList<Encomendas> encomendas,
                                         ArrayList<MeioTerrestre> meioTerrestres,
                                         ArrayList<MeioAquatico> meioAquaticos,
                                         ArrayList<MeioAereo> meioAereos) {

        if (!encomendas.isEmpty()) { // Verifica se existem encomendas salvas no ArrayList
            System.out.println("\n----- Listagem Encomendas -----");
            for (Encomendas encomenda : encomendas) { // Percorre o arraylist de encomendas
                System.out.println("\n\t*** Início encomenda ***");
                System.out.println(encomenda.toString() + "\n"); // Exibe as informações básicas da encomenda
                int IDTransporte = encomenda.getIDTransporte();     //  Passamos o ID do transporte associado à encomenda para uma variável local
                MeiosDeTransporte transporteAssociado = null;   //  Inicializa transporteAssociado como null

                // Procura o meio de transporte associado ao IDTransporte

                for (MeioTerrestre mt : meioTerrestres) {
                    if (mt.getID() == IDTransporte) {
                        transporteAssociado = mt;   //  Associa o transporte procurado à variável
                        break;
                    }
                }

                //  Verifica se o transporteAssociado ainda não foi atualizado
                if (transporteAssociado == null) {
                    for (MeioAquatico ma : meioAquaticos) {
                        if (ma.getID() == IDTransporte) {
                            transporteAssociado = ma;
                            break;
                        }
                    }
                }
                if (transporteAssociado == null) {
                    for (MeioAereo ma : meioAereos) {
                        if (ma.getID() == IDTransporte) {
                            transporteAssociado = ma;
                            break;
                        }
                    }
                }

                // Se o transporte associado foi encontrado, exibe suas informações
                if (transporteAssociado != null) {
                    System.out.println();
                    //System.out.println("Informações do meio de transporte associado:");
                    System.out.println(transporteAssociado.toString());
                    System.out.println("\t*** Fim transporte associado à encomenda ***");
                }
                else System.out.println("Meio de transporte associado apagado.");

            }
            System.out.println("\n--------------------------------\n");
        } else System.out.println("Nenhuma encomenda transportada!\n");

    }

    private static boolean removerTerrestre(ArrayList<MeioTerrestre>meioTerrestres, Scanner sc, boolean removerTransporte){
        //  Verifica que há transportes no arraylist
        if(!meioTerrestres.isEmpty()){
            System.out.println("Matrícula do transporte a remover: ");
            String matriculaProcurada = sc.next();

            for (MeioTerrestre meioTerrestre : meioTerrestres)
                if(matriculaProcurada.equals(meioTerrestre.getMatricula())) {    // Compara a matrícula a remover com as matrículas salvas no arrayList
                    System.out.println(meioTerrestre.getTipo() + " removido/a");
                    meioTerrestres.remove(meioTerrestre);   //  remove o transporte terrestre do arraylist
                    removerTransporte = true;   //  Verifica que a matrícula existe
                    break;  //  Caso encontre a matrícula sai do for each
                }

            if (!removerTransporte) //  Caso a matrícula não exista removerTransporte será falsa
                System.out.println(matriculaProcurada + " inexistente\n");

            return removerTransporte;    //  retorna o valor para atualizar a variável dentro do while
        }
        else System.out.println("Sem meios terrestres adicionados!\n");
        return false;
    }

    private static boolean removerAquatico(ArrayList<MeioAquatico>meioAquaticos, Scanner sc, boolean removerTransporte){
        //  Verifica que há transportes no arraylist
        if (!meioAquaticos.isEmpty()){
            System.out.println("Nome do transporte a remover: ");
            String nomeProcurado = sc.nextLine();

            for (MeioAquatico meioAquatico : meioAquaticos)
                if(nomeProcurado.equals(meioAquatico.getNome())) {    // Compara o nome a remover com os nomes salvos no arrayList
                    System.out.println(meioAquatico.getTipo() + " removido/a");
                    meioAquaticos.remove(meioAquatico);   //  remove o transporte aquático do arraylist
                    removerTransporte = true;   //  Verifica que o nome existe
                    break;  //  Caso encontre o nome sai do for each
                }

            if (!removerTransporte) //  Caso o nome não exista removerTransporte será falsa
                System.out.println(nomeProcurado + " inexistente\n");

            return removerTransporte;   //  retorna o valor para atualizar a variável dentro do while
        }else System.out.println("Sem meios aquáticos adicionados!\n");
        return false;
    }

    private static boolean removerAereo(ArrayList<MeioAereo>meioAereos, Scanner sc, boolean removerTransporte){
        //  Verifica que há transportes no arraylist
        if (!meioAereos.isEmpty()){
            int numeroProcurado = InputValidation.validateIntGT0(sc, "Número de registo do transporte a remover: ");

            for (MeioAereo meioAereo : meioAereos)
                if(numeroProcurado == meioAereo.getNumeroRegisto()) {    // Compara o número a remover com os números salvos no arrayList
                    System.out.println(meioAereo.getTipo() + " removido/a");
                    meioAereos.remove(meioAereo);   //  remove o transporte aéreo do arraylist
                    removerTransporte = true;   //  Verifica que o número existe
                    break;  //  Caso encontre o número sai do for each
                }

            if (!removerTransporte) //  Caso o número não exista removerTransporte será falsa
                System.out.println("\nNúmero de registo inexistente\n");

            return removerTransporte;   //  retorna o valor para atualizar a variável dentro do while
        }else System.out.println("Sem meios aéreos adicionados\n");
        return false;
    }

    private static void selecionaeTransporta(ArrayList<MeioTerrestre>meioTerrestres, Scanner sc, ArrayList<Encomendas>encomendas, ArrayList<MeioAquatico>meioAquaticos, ArrayList<MeioAereo>meioAereos){
        String meio;    //  Variável para o utilizador escolher o tipo de transporte

        System.out.println("Selecione como será transportada a encomenda (Terrestre, Aquático ou Aéreo): ");
        meio = sc.nextLine();

        //  Variáveis para comparar com a variável meio
        String terrestre = "Terrestre";
        String aquatico = "Aquatico";
        String aereo = "Aereo";

        if (meio.equalsIgnoreCase(terrestre))                       //  Comparaçao da variável meio com a terrestre
            encomendasTransporte(meioTerrestres, sc, encomendas);
        else if (meio.equalsIgnoreCase(aquatico))                   //  Comparaçao da variável meio com a aquatico
            encomendasTransporte(meioAquaticos, sc, encomendas);
        else if (meio.equalsIgnoreCase(aereo))                      //  Comparaçao da variável meio com a aereo
            encomendasTransporte(meioAereos, sc, encomendas);
        else System.out.println("Nome inválido");

    }

    private static void encomendasTransporte(ArrayList<? extends MeiosDeTransporte> meiosDeTransportes, Scanner sc, ArrayList<Encomendas> encomendas) {

        if (!meiosDeTransportes.isEmpty()) { // Verifica se existem meios de transporte terrestres salvos no ArrayList
            Encomendas novaEncomenda = new Encomendas(sc); // Cria uma nova encomenda com base na entrada do usuário

            boolean transporteEncontrado = false;

            while (true) {
                listarTransportes(meiosDeTransportes);  //  Lista todos os meios de um certo tipo
                int idTransporte = InputValidation.validateIntGT0(sc, "Introduza o ID do transporte: ");

                for (MeiosDeTransporte meiosDeTransporte : meiosDeTransportes) {    //  Percorre todos os meios consoante a escolha do usuário
                    if (idTransporte == meiosDeTransporte.getID()) {    //  Verifica se o ID escolhido pelo usuário existe
                        if (dimensoesAprovadas(meiosDeTransporte, novaEncomenda)) {     //  Verifica se a encomenda pode ser transportada
                            transporteEncontrado = true;    //  Atualiza a variável para sair do ciclo infinito
                            //  Associa a encomenda ao transporte e adiciona ao arraylist de encomnedas
                            novaEncomenda.associarEncomenda(idTransporte);
                            encomendas.add(novaEncomenda);
                            System.out.println("Encomenda transportada com sucesso!");
                            break; // Se a encomenda for adicionada , sai do for each
                        } else {
                            //  Caso as dimensões da encomenda forem maiores que as permitidas é mostrado as dimensões para o transporte escolhido
                            System.out.println("\nImpossível transportar a encomenda neste transporte! \nDimensões máximas:" +
                                    "\n\tAltura: " + meiosDeTransporte.getAlturaMax() + " m" + "\n\tLargura: " + meiosDeTransporte.getLarguraMax()
                                    + " m" + "\n\tComprimento: " + meiosDeTransporte.getProfundidadeMax() + " m");
                            transporteEncontrado = true;    //  Atualiza a variável para sair do ciclo infinito
                        }

                    }
                }
                if (transporteEncontrado) break;
                else System.out.println("Erro! Transporte inexistente! Por favor, selecione novamente.");

            }

        } else System.out.println("Sem transportes desse tipo adicionados!\n");

    }

    private static boolean dimensoesAprovadas(MeiosDeTransporte meiosDeTransporte, Encomendas encomendas) {
        //  Verifica se a encomenda pode ser transportada num determinado transporte
        return meiosDeTransporte.getAlturaMax() >= encomendas.getAlturaEnc() &&
                meiosDeTransporte.getLarguraMax() >= encomendas.getLarguraEnc() &&
                meiosDeTransporte.getProfundidadeMax() >= encomendas.getComprimentoEnc();

    }

}