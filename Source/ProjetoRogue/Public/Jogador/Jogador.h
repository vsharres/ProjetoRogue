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


/* Estrutura respons�vel por organizar e conter os stats do jogador. */
USTRUCT()
struct FJogadorStats
{
	GENERATED_USTRUCT_BODY()

	/* Vida atual do jogador. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "50.0", ClampMax = "500.0", UIMin = "50.0", UIMax = "500.0"), Category = "Jogador Struct")
		float Vida;

	/* Vida m�xima do jogador. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "50.0", ClampMax = "500.0", UIMin = "50.0", UIMax = "500.0"), Category = "Jogador Struct")
		float VidaMaxima;

	/* Energia atual do jogador. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "300.0", UIMin = "0.0", UIMax = "300.0"), Category = "Jogador Struct")
		float Energia;

	/* Energia m�xima do jogador. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "300.0", UIMin = "0.0", UIMax = "300.0"), Category = "Jogador Struct")
		float EnergiaMax;
	/* Velocidade de movimenta��o do jogador. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "600.0", ClampMax = "1800.0", UIMin = "600.0", UIMax = "1800.0"), Category = "Jogador Struct")
		float VelocidadeMov;
	/* Dano causado pelo jogador. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "5.0", ClampMax = "50.0", UIMin = "5.0", UIMax = "50.0"), Category = "Jogador Struct")
		float Dano;
	/* Frequ�ncia de tiro do jogador. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "1.0", ClampMax = "10.0", UIMin = "1.0", UIMax = "10.0"), Category = "Jogador Struct")
		float FireRate;
	/* Precisao dos tiros do jogador. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "1.0", ClampMax = "30.0", UIMin = "1.0", UIMax = "30.0"), Category = "Jogador Struct")
		float Precisao;
	/* Velocidade do proj�til do jogador. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "1000.0", ClampMax = "7000.0", UIMin = "1000.0", UIMax = "7000.0"), Category = "Jogador Struct")
		float VelProjetil;

	/* Overload do operador de atribui��o por soma, para facilitar mudan�as nos stats. */
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

	/* Overload do operador de atribui��o por subtra��o, para facilitar mudan�as nos stats. */
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
	* Fun��o para realizar um clamp no valor dos stats a serem adicionar, para garantir que os limites nao ser�o passados, fun��o usada quando um item � aplicado.
	* @param itemStats - Refer�ncia constante ao item a ser adicionado.
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

		if (itemStats.IncrementaVel + this->VelocidadeMov > VELOCIDADEMOV_MAX) //checar velocidade de movimenta��o maxima
		{
			aRetornar.IncrementaVida = VELOCIDADEMOV_MAX - this->VelocidadeMov;
		}
		else if (itemStats.IncrementaVel + this->VelocidadeMov < VELOCIDADEMOV_MIN) //checar velocidade de movimenta��o minima
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
	* Fun��o  para garantir que os limites dos stats nao ser�o passados
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
	* Fun��o para adicionar vida aos stats.
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
	* Fun��o para adicionar energia aos stats.
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
	* Fun��o para setar novos stats.
	* @param stats - refer�ncia constante aos stats a serem setados.
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

		ChecarValores(); //checar os valores para n�o passar dos limites
	}

	//Construtor padr�o
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

		ChecarValores(); //checar os valores para n�o passar dos limites
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

		ChecarValores(); //checar os valores para n�o passar dos limites
	}

};

/* Enumera��o que os tipos de intera��o que o jogador pode fazer */
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

/* Enumera��o com o tipo do promp de tutorial. */
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

/* Enumera��o com o estado de inicializa��o do jogador atual. */
UENUM(BlueprintType)
enum class EInicializarEstado :uint8
{
	BOOTUP,
	NOVOLEVEL,
	JOGAR,
};

/*
* Classe derivada da classe ACharacter
* Classe respons�vel por toda a funcionalidade do jogador.
*/
UCLASS()
class PROJETOROGUE_API AJogador : public ACharacter, public IDanoInterface //Interface de dano
{
	GENERATED_BODY()


public:
	/* Nome do prot�tipo atual. */
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

	/* Dura��o do cooldown do item ativo. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "1.0", UIMax = "5.0"), Category = "Item")
		float TempoCooldown;

	/* Velocidade com que o cooldown � alterado. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "0.1", UIMax = "10.0"), Category = "Item")
		float CooldDownRate;

	/* Booleando indiciando se o jogador possui a chave. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		bool bPossuiChave;

	/* Array com os itens passivos que o jogador possui. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		TArray<class UItemPassivo*> ItensPassivos;

	/* Booleano indicando se o jogador j� encontrou o item da fase. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		bool bItemEncontrado;

	//PROJETIL

	/* N�mero de proj�teis dentro do pool de proj�teis. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projetil")
		int32 NumProjeteis;

	/* Classe do tipo de proj�til inicial. */
	UPROPERTY(EditDefaultsOnly, Category = "Projetil")
		TSubclassOf<class UItemProjetil> ProjetilInicial;

	/* Classe do proj�til encontrado. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projetil")
		TSubclassOf<UItemProjetil> ProjetilEncontrado;

	/* Pr�j�til sendo utilizado no momento. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projetil")
		UItemProjetil* ProjetilAtual;

	/* Array com todos os proj�teis que podem ser disparado. Esse pool � est�tico, isto �, todos os proj�teis s�o alocados inicialmente.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projetil")
		TArray<AProjectil*> ProjetilPool;

	/* Nome do socket no canhao da onde os proj�teis s�o atirados. */
	UPROPERTY()
		FName ProjetilSocket;

	/* Cor atual dos proj�teis. */
	UPROPERTY(BlueprintReadOnly, Category = Projetil)
		FLinearColor ProjetilCor;

	/* Construtor Padr�o. */
	AJogador(const FObjectInitializer& ObjectInitializer);

	/*
	* Fun��o de inicializa��o do jogador.
	*/
	UFUNCTION(BlueprintCallable, Category = "Jogador")
		void InicializarJogador();

	/*
	* Fun��o para gerar o nome da vers�o do prot�tipo do jogador.
	* @param index - �ndice da vers�o do jogador.
	*/
	UFUNCTION(BlueprintCallable, Category = "Nome")
		void GerarNome(int32 index);

	/*
	* Fun��o para atulizar as propriedades de movimenta��o com os stats atuais do jogador.
	*/
	UFUNCTION()
		void AtualizarPropriedadesComStats();

	/*
	* Fun��o para inicializar um proj�til dentro do pool de proj�teis.
	* @param bDesativar - Argumento opicional para desativar os proj�teis.
	*/
	UFUNCTION()
		void InicializarProjetil(bool bDesativar = false);

	/*
	* Fun��o para gerar o pool de proj�teis.
	*/
	UFUNCTION(BlueprintCallable, Category = "Projetil")
		void GerarProjetilPool();

	/*
	* Fun��o para checar se o jogador ainda est� vivo.
	* @return verdadeiro se o jogador est� vivo.
	*/
	UFUNCTION(BlueprintPure, Category = Jogador)
		bool EstaVivo();

	/*
	* Fun��o para adicionar vida ao jogador.
	* @param vida - float com a vida a ser adicionada.
	*/
	UFUNCTION(BlueprintCallable, Category = "Jogador")
		void AdicionarVida(float vida);
	/*
	* Fun��o para adicionar energia ao jogador.
	* @param energia - float com a energia a ser adicionada.
	*/
	UFUNCTION(BlueprintCallable, Category = "Jogador")
		void AdicionarEnerngia(float energia);

	/*
	* Fun��o para adicionar scrap ao jogador.
	* @param valor - inteiro com o n�mero de scrap a ser adicionado.
	*/
	UFUNCTION(BlueprintCallable, Category = "Jogador")
		void AdicionarMoedas(int32 valor);

	/*
	* Fun��o para salvar as propriedades do jogador.
	*/
	UFUNCTION(BlueprintCallable, Category = "Jogo")
		void SalvarJogador();

	/*
	* Fun��o para carregar o jogador.
	*/
	UFUNCTION(BlueprintCallable, Category = "Jogo")
		void CarregarJogador();

	/*
	* Fun��o para criar as propriedades de um novo jogador.
	*/
	UFUNCTION(BlueprintCallable, Category = "Jogo")
		void NovoJogador();

	/*
	* Fun��o para usar o item ativo.
	* @param bDesativar - argumento opicional para desativar um item.
	*/
	UFUNCTION(BlueprintCallable, Category = "Item")
		void UsarItem(bool bDesativar = false);

	/*
	* Evento para atualizar o mesh do canh�o.
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
	* @param dano - Refer�ncia constante ao dano a ser tomado.
	* @param projetil - Ponteiro opicional ao proj�til que causou o dano
	* @param Hit -  Estrutura com os resultados da colis�o que causou o dano.
	*/
	UFUNCTION(BlueprintCallable, Category = "Jogador")
		virtual void ReceberDano(const float& dano, AProjectil* projetil, const FHitResult& Hit) override;

	/*
	* Interface para aplicar os stats do jogador ao proj�til atirado.
	* @param projetil - Ponteiro ao proj�til atirado.
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
	* Evento de blueprint para gerar o semi c�rculo de dano.
	* @param Hit - Refer�ncia constante aos resultados de colis�o que causou dano ao jogador.
	*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (DisplayName = "Gerar Circulo Dano", Keywords = "Gerar Circulo Dano"), Category = "Jogador")
		void GerarCirculoDano(const FHitResult& Hit);

	/* Fun��o para fazer o cooldown do item. Fun��o para ser chamada durante o Tick do jogador.*/
	UFUNCTION()
		void ItemCooldown(float DeltaTime);

	/* Evento de blueprint para fazer o reset do timer de cooldown do item. */
	UFUNCTION(BlueprintImplementableEvent, Category = "Jogador")
		void ResetTimer();

};
