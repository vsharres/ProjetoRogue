// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "DanoInterface.h"
#include "Item.h"
#include "Jogador.generated.h"

//Constantes
const float VIDAMAX_MAX = 500.0F;
const float VIDAMAX_MIN = 50.0f;
const float ENERGIA_MAX = 300;
const float ENERGIA_MIN = 0;
const float VELOCIDADEMOV_MAX = 1800.0f;
const float VELOCIDADEMOV_MIN = 600.0f;
const float DANO_MAX = 50.0f;
const float DANO_MIN = 5;
const float FIRERATE_MAX = 10.0f;
const float FIRERATE_MIN = 1.0f;
const float PRECISAO_MAX = 30.0f;
const float PRECISAO_MIN = 1.0f;
const float VELOCIDADEPROJ_MAX = 7000.0f;
const float VELOCIDADEPROJ_MIN = 1000.f;


/* Estrutura responsável por organizar e conter os stats do jogador. */
USTRUCT()
struct FJogadorStats
{
	GENERATED_USTRUCT_BODY()

	/* Vida atual do jogador. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "50.0", ClampMax = "500.0", UIMin = "50.0", UIMax = "500.0"), Category = "Jogador Struct")
		float Vida;

	/* Vida máxima do jogador. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "50.0", ClampMax = "500.0", UIMin = "50.0", UIMax = "500.0"), Category = "Jogador Struct")
		float VidaMaxima;

	/* Energia atual do jogador. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "300.0", UIMin = "0.0", UIMax = "300.0"), Category = "Jogador Struct")
		float Energia;

	/* Energia máxima do jogador. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "300.0", UIMin = "0.0", UIMax = "300.0"), Category = "Jogador Struct")
		float EnergiaMax;
	/* Velocidade de movimentação do jogador. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "600.0", ClampMax = "1800.0", UIMin = "600.0", UIMax = "1800.0"), Category = "Jogador Struct")
		float VelocidadeMov;
	/* Dano causado pelo jogador. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "5.0", ClampMax = "50.0", UIMin = "5.0", UIMax = "50.0"), Category = "Jogador Struct")
		float Dano;
	/* Frequência de tiro do jogador. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "1.0", ClampMax = "10.0", UIMin = "1.0", UIMax = "10.0"), Category = "Jogador Struct")
		float FireRate;
	/* Precisao dos tiros do jogador. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "1.0", ClampMax = "30.0", UIMin = "1.0", UIMax = "30.0"), Category = "Jogador Struct")
		float Precisao;
	/* Velocidade do projétil do jogador. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "1000.0", ClampMax = "7000.0", UIMin = "1000.0", UIMax = "7000.0"), Category = "Jogador Struct")
		float VelProjetil;

	/* Overload do operador de atribuição por soma, para facilitar mudanças nos stats. */
	FORCEINLINE FJogadorStats& operator+=(const FItemStats& itemStats)
	{
		this->VidaMaxima += itemStats.IncrementaVidaMax;
		this->EnergiaMax += itemStats.IncrementaEnergiaMax;
		this->VelocidadeMov += itemStats.IncrementaVel;
		this->FireRate += itemStats.IncrementaFireRate;
		this->Dano += itemStats.IncrementaDano;
		this->Precisao += itemStats.IncrementaPrecisao;
		this->VelProjetil += itemStats.IncrementaVelProjetil;

		AdicionarEnergia(itemStats.IncrementaEnergia); //Adicionar a nova energia calculada
		AdicionarVida(itemStats.IncrementaVida); //Adicionar a nova vida calculada

		ChecarValores(); //garantir que os valores nao passam dos valores limites.

		return *this;
	}

	/* Overload do operador de atribuição por subtração, para facilitar mudanças nos stats. */
	FORCEINLINE FJogadorStats& operator-=(const FItemStats& itemStats)
	{
		this->VidaMaxima -= itemStats.IncrementaVidaMax;
		this->EnergiaMax -= itemStats.IncrementaEnergiaMax;
		this->VelocidadeMov -= itemStats.IncrementaVel;
		this->FireRate -= itemStats.IncrementaFireRate;
		this->Dano -= itemStats.IncrementaDano;
		this->Precisao -= itemStats.IncrementaPrecisao;
		this->VelProjetil -= itemStats.IncrementaVelProjetil;

		AdicionarEnergia(-itemStats.IncrementaEnergia); //remover a nova energia calculada
		AdicionarVida(-itemStats.IncrementaVida); //remover a nova vida calculada

		ChecarValores(); //garantir que os valores nao passam dos valores limites.

		return *this;
	}

	/* 
	* Função para realizar um clamp no valor dos stats a serem adicionar, para garantir que os limites nao serão passados, função usada quando um item é aplicado.
	* @param itemStats - Referência constante ao item a ser adicionado.
	* @return o novo stat calculado.
	*/
	FORCEINLINE FItemStats ClampAdicionarStats(const FItemStats& itemStats)
	{
		FItemStats aRetornar;

		if (itemStats.IncrementaDano + this->Dano > DANO_MAX) //checar dano maximo
		{
			aRetornar.IncrementaDano = DANO_MAX - this->Dano;
		}
		else if (itemStats.IncrementaDano + this->Dano < DANO_MIN) //checar dano minimo
		{
			aRetornar.IncrementaDano = DANO_MIN - this->Dano;
		}
		else
		{
			aRetornar.IncrementaDano = itemStats.IncrementaDano;
		}

		if (itemStats.IncrementaFireRate + this->FireRate > FIRERATE_MAX) //checar fire rate maximo
		{
			aRetornar.IncrementaFireRate = FIRERATE_MAX - this->FireRate;
		}
		else if (itemStats.IncrementaFireRate + this->FireRate < FIRERATE_MIN) // checar fire rate minimo
		{
			aRetornar.IncrementaFireRate = FIRERATE_MIN - this->FireRate;
		}
		else
		{
			aRetornar.IncrementaFireRate = itemStats.IncrementaFireRate;
		}

		if (itemStats.IncrementaPrecisao + this->Precisao > PRECISAO_MAX) //checar precisao maxima
		{
			aRetornar.IncrementaPrecisao = PRECISAO_MAX - this->Precisao;
		}
		else if (itemStats.IncrementaPrecisao + this->Precisao < PRECISAO_MIN) //checar precisao minima
		{
			aRetornar.IncrementaPrecisao = PRECISAO_MIN - this->Precisao;
		}
		else
		{
			aRetornar.IncrementaPrecisao = itemStats.IncrementaPrecisao;
		}

		if (itemStats.IncrementaVel + this->VelocidadeMov > VELOCIDADEMOV_MAX) //checar velocidade de movimentação maxima
		{
			aRetornar.IncrementaVida = VELOCIDADEMOV_MAX - this->VelocidadeMov;
		}
		else if (itemStats.IncrementaVel + this->VelocidadeMov < VELOCIDADEMOV_MIN) //checar velocidade de movimentação minima
		{
			aRetornar.IncrementaVel = VELOCIDADEMOV_MIN - this->VelocidadeMov;
		}
		else
		{
			aRetornar.IncrementaVel = itemStats.IncrementaVel;
		}

		if (itemStats.IncrementaVelProjetil + this->VelProjetil > VELOCIDADEPROJ_MAX) //checar velocidade do projetil maxima
		{
			aRetornar.IncrementaVelProjetil = VELOCIDADEPROJ_MAX - this->VelProjetil;
		}
		else if (itemStats.IncrementaVelProjetil + this->VelProjetil < VELOCIDADEPROJ_MIN) //checar velocidade do projetil minima
		{
			aRetornar.IncrementaVelProjetil = VELOCIDADEPROJ_MIN - this->VelProjetil;
		}
		else
		{
			aRetornar.IncrementaVelProjetil = itemStats.IncrementaVelProjetil;
		}

		if (itemStats.IncrementaVidaMax + this->VidaMaxima > VIDAMAX_MAX) //checar vida maxima
		{
			aRetornar.IncrementaVidaMax = VIDAMAX_MAX - this->VidaMaxima;
		}
		else if (itemStats.IncrementaVidaMax + this->VidaMaxima < VIDAMAX_MIN) // checar vida minima
		{
			aRetornar.IncrementaVidaMax = VIDAMAX_MIN - this->VidaMaxima;
		}
		else
		{
			aRetornar.IncrementaVidaMax = itemStats.IncrementaVidaMax;
		}

		if (itemStats.IncrementaVida + this->Vida > VidaMaxima) // checar vida atual
		{
			aRetornar.IncrementaVida = VidaMaxima - this->Vida;
		}
		else if (itemStats.IncrementaVida + this->Vida < VIDAMAX_MIN)
		{
			aRetornar.IncrementaVida = VIDAMAX_MIN - this->Vida;
		}
		else
		{
			aRetornar.IncrementaVida = itemStats.IncrementaVida;
		}

		if (itemStats.IncrementaEnergiaMax + this->EnergiaMax > ENERGIA_MAX) //checar energia maxima
		{
			aRetornar.IncrementaEnergiaMax = ENERGIA_MAX - this->EnergiaMax;
		}
		else if (itemStats.IncrementaEnergiaMax + this->EnergiaMax < ENERGIA_MIN) //checar energia minima
		{
			aRetornar.IncrementaEnergiaMax = ENERGIA_MIN - this->EnergiaMax;
		}
		else
		{
			aRetornar.IncrementaEnergiaMax = itemStats.IncrementaEnergiaMax;
		}

		if (itemStats.IncrementaEnergia + this->Energia > EnergiaMax) // checar energia
		{
			aRetornar.IncrementaEnergia = EnergiaMax - this->Energia;
		}
		else if (itemStats.IncrementaEnergia + this->Energia < ENERGIA_MIN)
		{
			aRetornar.IncrementaEnergia = ENERGIA_MIN - this->Energia;
		}
		else
		{
			aRetornar.IncrementaEnergia = itemStats.IncrementaEnergia;
		}

		return aRetornar;
	}

	/*
	* Função  para garantir que os limites dos stats nao serão passados
	*/
	FORCEINLINE void ChecarValores()
	{
		if (VidaMaxima > VIDAMAX_MAX)
		{
			VidaMaxima = VIDAMAX_MAX;
		}
		else if (VidaMaxima < VIDAMAX_MIN)
		{
			VidaMaxima = VIDAMAX_MIN;
		}

		if (VelocidadeMov > VELOCIDADEMOV_MAX)
		{
			VelocidadeMov = VELOCIDADEMOV_MAX;
		}
		else if (VelocidadeMov < VELOCIDADEMOV_MIN)
		{
			VelocidadeMov = VELOCIDADEMOV_MIN;
		}

		if (FireRate > FIRERATE_MAX)
		{
			FireRate = FIRERATE_MAX;
		}
		else if (FireRate < FIRERATE_MIN)
		{
			FireRate = FIRERATE_MIN;
		}

		if (Dano > DANO_MAX)
		{
			Dano = DANO_MAX;
		}
		else if (Dano < DANO_MIN)
		{
			Dano = DANO_MIN;
		}

		if (Precisao > PRECISAO_MAX)
		{
			Precisao = PRECISAO_MAX;
		}
		else if (Precisao < PRECISAO_MIN)
		{
			Precisao = PRECISAO_MIN;
		}

		if (VelProjetil > VELOCIDADEPROJ_MAX)
		{
			VelProjetil = VELOCIDADEPROJ_MAX;
		}
		else if (VelProjetil < VELOCIDADEPROJ_MIN)
		{
			VelProjetil = VELOCIDADEPROJ_MIN;
		}

		if (EnergiaMax > ENERGIA_MAX)
		{
			EnergiaMax = ENERGIA_MAX;
		}
		else if (EnergiaMax < ENERGIA_MIN)
		{
			EnergiaMax = ENERGIA_MIN;
		}

	}

	/*
	* Função para adicionar vida aos stats.
	* @param vidaAdicionada - float com a vida a ser adicionada
	*/
	FORCEINLINE void AdicionarVida(float vidaAdicionada)
	{
		Vida += vidaAdicionada;

		if (Vida > VidaMaxima) //checar limites
		{
			Vida = VidaMaxima;
		}
		else if (Vida < 0)
		{
			Vida = 0;
		}

	}

	/*
	* Função para adicionar energia aos stats.
	* @param energidaAdicionada - float com a energia a ser adicionada
	*/
	FORCEINLINE void AdicionarEnergia(int32 energidaAdicionada)
	{
		Energia += energidaAdicionada;

		if (Energia > EnergiaMax) //checar limites
		{
			Energia = EnergiaMax;
		}
		else if (Energia < 0)
		{
			Energia = 0;
		}
	}

	/*
	* Função para setar novos stats.
	* @param stats - referência constante aos stats a serem setados.
	*/
	FORCEINLINE void SetStats(const FJogadorStats& stats)
	{
		this->Vida = stats.Vida;
		this->VidaMaxima = stats.VidaMaxima;
		this->Energia = stats.Energia;
		this->EnergiaMax = stats.EnergiaMax;
		this->VelocidadeMov = stats.VelocidadeMov;
		this->Dano = stats.Dano;
		this->FireRate = stats.FireRate;
		this->Precisao = stats.Precisao;
		this->VelProjetil = stats.VelProjetil;

		ChecarValores(); //checar os valores para não passar dos limites
	}

	//Construtor padrão
	FJogadorStats(float vidMax = 100.0f, float velMov = 600.0f, float fireRate = 0.05f, float dano = 5.0f, float precisao = 5.0f, float velProjetil = 1500.0f, float energia = 100)
	{
		VidaMaxima = vidMax;
		VelocidadeMov = velMov;
		FireRate = fireRate;
		Dano = dano;
		Precisao = precisao;
		VelProjetil = velProjetil;
		Energia = energia;
		EnergiaMax = Energia;
		Vida = VidaMaxima;

		ChecarValores(); //checar os valores para não passar dos limites
	}

	//Construtor por copia.
	FJogadorStats(const FJogadorStats& Outro)
	{
		VidaMaxima = Outro.VidaMaxima;
		VelocidadeMov = Outro.VelocidadeMov;
		FireRate = Outro.FireRate;
		Dano = Outro.Dano;
		Precisao = Outro.Precisao;
		VelProjetil = Outro.VelProjetil;
		Energia = Outro.Energia;
		EnergiaMax = Outro.EnergiaMax;
		Vida = Outro.Vida;

		ChecarValores(); //checar os valores para não passar dos limites
	}

};

/* Enumeração que os tipos de interação que o jogador pode fazer */
UENUM(BlueprintType)
enum class ETipoInteracao : uint8
{
	NENHUMA,
	CHAVE,
	ITEM,
	LOJA,
	ELEVADOR,
	HOLOLOG,
	TUTORIALPROMP
};

/* Enumeração com o tipo do promp de tutorial. */
UENUM(BlueprintType)
enum class ETutorialPromp :uint8
{
	PORTACHEFE,
	CHAVE,
	LOJA,
	ITEMPASSIVO,
	ITEMATIVO,
	INVENTARIO
};

/* Enumeração com o estado de inicialização do jogador atual. */
UENUM(BlueprintType)
enum class EInicializarEstado :uint8
{
	BOOTUP,
	NOVOLEVEL,
	JOGAR,
};

/*
* Classe derivada da classe ACharacter
* Classe responsável por toda a funcionalidade do jogador.
*/
UCLASS()
class PROJETOROGUE_API AJogador : public ACharacter, public IDanoInterface //Interface de dano
{
	GENERATED_BODY()


public:
	/* Nome do protótipo atual. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nome")
		FString Nome;

	/* Stats do jogador. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		FJogadorStats Stats;

	/* Scrap total do jogador */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Moedas")
		int32 Moedas;

	//ITENS
	/* Cooldown atual do item ativo. */
	UPROPERTY(BlueprintReadWrite, Category = "Item")
		float CooldownAtual;

	/* Duração do cooldown do item ativo. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "1.0", UIMax = "5.0"), Category = "Item")
		float TempoCooldown;

	/* Velocidade com que o cooldown é alterado. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "0.1", UIMax = "10.0"), Category = "Item")
		float CooldDownRate;

	/* Booleando indiciando se o jogador possui a chave. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		bool bPossuiChave;

	/* Array com os itens passivos que o jogador possui. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		TArray<class UItemPassivo*> ItensPassivos;

	/* Booleano indicando se o jogador já encontrou o item da fase. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		bool bItemEncontrado;

	//PROJETIL

	/* Número de projéteis dentro do pool de projéteis. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projetil")
		int32 NumProjeteis;

	/* Classe do tipo de projétil inicial. */
	UPROPERTY(EditDefaultsOnly, Category = "Projetil")
		TSubclassOf<class UItemProjetil> ProjetilInicial;

	/* Classe do projétil encontrado. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projetil")
		TSubclassOf<UItemProjetil> ProjetilEncontrado;

	/* Prójétil sendo utilizado no momento. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projetil")
		UItemProjetil* ProjetilAtual;

	/* Array com todos os projéteis que podem ser disparado. Esse pool é estático, isto é, todos os projéteis são alocados inicialmente.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projetil")
		TArray<AProjectil*> ProjetilPool;

	/* Nome do socket no canhao da onde os projéteis são atirados. */
	UPROPERTY()
		FName ProjetilSocket;

	/* Cor atual dos projéteis. */
	UPROPERTY(BlueprintReadOnly, Category = Projetil)
		FLinearColor ProjetilCor;

	/* Construtor Padrão. */
	AJogador(const FObjectInitializer& ObjectInitializer);

	/*
	* Função de inicialização do jogador.
	*/
	UFUNCTION(BlueprintCallable, Category = "Jogador")
		void InicializarJogador();

	/*
	* Função para gerar o nome da versão do protótipo do jogador.
	* @param index - Índice da versão do jogador.
	*/
	UFUNCTION(BlueprintCallable, Category = "Nome")
		void GerarNome(int32 index);

	/*
	* Função para atulizar as propriedades de movimentação com os stats atuais do jogador.
	*/
	UFUNCTION()
		void AtualizarPropriedadesComStats();

	/*
	* Função para inicializar um projétil dentro do pool de projéteis.
	* @param bDesativar - Argumento opicional para desativar os projéteis.
	*/
	UFUNCTION()
		void InicializarProjetil(bool bDesativar = false);

	/*
	* Função para gerar o pool de projéteis.
	*/
	UFUNCTION(BlueprintCallable, Category = "Projetil")
		void GerarProjetilPool();

	/*
	* Função para checar se o jogador ainda está vivo.
	* @return verdadeiro se o jogador está vivo.
	*/
	UFUNCTION(BlueprintPure, Category = Jogador)
		bool EstaVivo();

	/*
	* Função para adicionar vida ao jogador.
	* @param vida - float com a vida a ser adicionada.
	*/
	UFUNCTION(BlueprintCallable, Category = "Jogador")
		void AdicionarVida(float vida);
	/*
	* Função para adicionar energia ao jogador.
	* @param energia - float com a energia a ser adicionada.
	*/
	UFUNCTION(BlueprintCallable, Category = "Jogador")
		void AdicionarEnerngia(float energia);

	/*
	* Função para adicionar scrap ao jogador.
	* @param valor - inteiro com o número de scrap a ser adicionado.
	*/
	UFUNCTION(BlueprintCallable, Category = "Jogador")
		void AdicionarMoedas(int32 valor);

	/*
	* Função para salvar as propriedades do jogador.
	*/
	UFUNCTION(BlueprintCallable, Category = "Jogo")
		void SalvarJogador();

	/*
	* Função para carregar o jogador.
	*/
	UFUNCTION(BlueprintCallable, Category = "Jogo")
		void CarregarJogador();

	/*
	* Função para criar as propriedades de um novo jogador.
	*/
	UFUNCTION(BlueprintCallable, Category = "Jogo")
		void NovoJogador();

	/*
	* Função para usar o item ativo.
	* @param bDesativar - argumento opicional para desativar um item.
	*/
	UFUNCTION(BlueprintCallable, Category = "Item")
		void UsarItem(bool bDesativar = false);

	/*
	* Evento para atualizar o mesh do canhão.
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = Jogador)
		void AtualizarMesh();

	//INTERFACES

	/* Override do tick do jogador. */
	virtual void Tick(float DeltaSeconds) override;

	/* Overload do evento de EndPlay do jogador. */
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/*
	* Interface para o jogador receber dano.
	* @param dano - Referência constante ao dano a ser tomado.
	* @param projetil - Ponteiro opicional ao projétil que causou o dano
	* @param Hit -  Estrutura com os resultados da colisão que causou o dano.
	*/
	UFUNCTION(BlueprintCallable, Category = "Jogador")
		virtual void ReceberDano(const float& dano, AProjectil* projetil, const FHitResult& Hit) override;

	/*
	* Interface para aplicar os stats do jogador ao projétil atirado.
	* @param projetil - Ponteiro ao projétil atirado.
	*/
	UFUNCTION(BlueprintCallable, Category = "Projetil")
		virtual void AplicarStatsProjetil(AProjectil* projetil) override;

	/* Evento de blueprint para o jogador atirar. */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (DisplayName = "Atirar", Keywords = "Atirar"), Category = "Jogador")
		void Atirar();

	/* Evento de blueprint disparado quando o jogador morreu. */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (DisplayName = "Jogador Morreu", Keywords = "Jogador Morreu"), Category = "Jogador")
		void JogadorMorreu();

	/* 
	* Evento de blueprint para gerar o pop up de dano. 
	* @param dano - dano causado.
	* @param alvo - Inimigo que foi atingido.
	* @param projetil - projetil que causou o dano
	*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (DisplayName = "Gerar DanoPopUp", Keywords = "Gerar Dano PopUp"), Category = "Jogador")
		void GerarDanoPopUp(float dano, AInimigo* alvo, AProjectil* projetil);

	/* 
	* Evento de blueprint para gerar o pop up do pick up.
	* @param novoPickUp - Pick que foi pego.
	*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (DisplayName = "Gerar PickUp PopUp", Keywords = "Gerar PickUp PopUp"), Category = "Jogador")
		void GerarPickUpPopUp(class APickUp* novoPicUp);

	/* 
	* Evento de blueprint para gerar o item de pop up. 
	* @param novoItem - Item que foi pego.
	*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (DisplayName = "Gerar Item PopUp", Keywords = "Gerar Item PopUp"), Category = "Jogador")
		void GerarItemPopUp(class AActor* novoItem);
	/* 
	* Evento de blueprint para gerar o semi círculo de dano.
	* @param Hit - Referência constante aos resultados de colisão que causou dano ao jogador.
	*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (DisplayName = "Gerar Circulo Dano", Keywords = "Gerar Circulo Dano"), Category = "Jogador")
		void GerarCirculoDano(const FHitResult& Hit);

	/* Função para fazer o cooldown do item. Função para ser chamada durante o Tick do jogador.*/
	UFUNCTION()
		void ItemCooldown(float DeltaTime);

	/* Evento de blueprint para fazer o reset do timer de cooldown do item. */
	UFUNCTION(BlueprintImplementableEvent, Category = "Jogador")
		void ResetTimer();

};
