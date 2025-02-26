#pragma once

#include "NativeGameplayTags.h"
#include "Animation/AnimMontage.h"
#include "Engine/EngineTypes.h"
#include "ALSXTStructs.generated.h"

class UAnimMontage;
class UCurveFloat;
class UCurveVector;

USTRUCT(BlueprintType)
struct ALSXT_API FExtendedHitResult
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	bool Hit {false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	float Mass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	float Velocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	FVector Direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	FVector Impulse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	FGameplayTag DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	FHitResult HitResult;

};

USTRUCT(BlueprintType)
struct ALSXT_API FDoubleHitResult
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	FGameplayTag CollisionType;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	FGameplayTag ImpactType;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	FGameplayTag ImpactForm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	FGameplayTag ImpactLocation; // Calculated from Get Location from Bone Name

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	FGameplayTag ImpactSide; // Calculated from Get Side from Hit

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	FGameplayTag Strength; // Calculated by Mass and Volume

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	FExtendedHitResult HitResult;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	FExtendedHitResult OriginHitResult;

};

USTRUCT(BlueprintType)
struct ALSXT_API FAttackDoubleHitResult
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	FGameplayTag Overlay;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	FGameplayTag Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	FGameplayTag Strength; // Explicitly set in AnimNotify or Attack code

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	float BaseDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	FDoubleHitResult DoubleHitResult;

};

USTRUCT(BlueprintType)
struct ALSXT_API FTargetHitResultEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	bool Valid { false };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	float DistanceFromPlayer{ 340282346638528859811704183484516925440.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	float AngleFromCenter {361.0f};

	UPROPERTY(BlueprintReadOnly, Meta = (AllowPrivateAccess))
	FHitResult HitResult;

};

USTRUCT(BlueprintType)
struct ALSXT_API FActionMontageInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
	TObjectPtr<UAnimMontage> Montage { nullptr };

	// UnarmedAttack time to blend in amount curve.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
	TObjectPtr<UCurveFloat> BlendInCurve { nullptr };

	// UnarmedAttack time to interpolation, horizontal and vertical correction amounts curve.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
	TObjectPtr<UCurveVector> InterpolationAndCorrectionAmountsCurve { nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
	FVector StartRelativeLocation{-65.0f, 0.0f, -100.0f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", Meta = (ClampMin = 0))
	FVector2D ReferenceHeight{50.0f, 100.0f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", Meta = (ClampMin = 0))
	FVector2D StartTime{0.5f, 0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", Meta = (ClampMin = 0))
	FVector2D PlayRate{1.0f, 1.0f};

	bool operator==(const FActionMontageInfo& other) const
	{
		return (other.Montage == Montage) && (other.BlendInCurve == BlendInCurve) && (other.InterpolationAndCorrectionAmountsCurve == InterpolationAndCorrectionAmountsCurve);
	}
};

USTRUCT(BlueprintType)
struct ALSXT_API FSyncedActionMontageInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	TArray<FActionMontageInfo> AttackerSyncedMontages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	TArray<FActionMontageInfo> TargetSyncedMontages;

};

USTRUCT(BlueprintType)
struct ALSXT_API FImpactForm
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	FGameplayTag ImpactReactionForm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	TArray<FActionMontageInfo> BlockingMontages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	TArray<FActionMontageInfo> RegularMontages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	TArray<FActionMontageInfo> RecoveryMontages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	TArray<FActionMontageInfo> DeathMontages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	FActionMontageInfo DefaultFallbackMontage;
};

USTRUCT(BlueprintType)
struct ALSXT_API FImpactReactionSide
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	FGameplayTag ImpactReactionSide;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	TArray <FImpactForm> ImpactReactionForms;
};

USTRUCT(BlueprintType)
struct ALSXT_API FImpactReactionStrength
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	FGameplayTag ImpactReactionStrength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	TArray <FImpactReactionSide> ImpactReactionSides;
};

USTRUCT(BlueprintType)
struct ALSXT_API FImpactReactionLocation
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	FGameplayTag ImpactReactionLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	TArray <FImpactReactionStrength> ImpactReactionStrengths;
};

USTRUCT(BlueprintType)
struct ALSXT_API FImpactReactionOverlayMode
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	FGameplayTag OverlayMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	TArray <FImpactReactionLocation> ImpactReactionLocations;
};

USTRUCT(BlueprintType)
struct ALSXT_API FUnarmedAttackStance
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	FGameplayTag UnarmedAttackStance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	FGameplayTag AnimationType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	TArray<FActionMontageInfo> MontageInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	TArray<FActionMontageInfo> RegularMontages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	TArray<FSyncedActionMontageInfo> SyncedMontages;
};

USTRUCT(BlueprintType)
struct ALSXT_API FUnarmedAttackStrength
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	FGameplayTag UnarmedAttackStrength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	TArray <FUnarmedAttackStance> UnarmedAttackStances;
};

USTRUCT(BlueprintType)
struct ALSXT_API FUnarmedAttackType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	FGameplayTag UnarmedAttackType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	TArray<FUnarmedAttackStrength> UnarmedAttackStrengths;
};