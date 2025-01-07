#include "Model.h"
#include "Vector3.h"
#include "Viewprojection.h"
#include "WorldTransform.h"
#include <string>
#include <vector>

enum class MapChipType {
	kBlank,  // 空白
	kBlock,  // ブロック
	kBlock1, // ブロック
	kBlock2, // 透明ブロック
	kBlock3, // ブロック
	kGoal,
	kATK,
	kHPup, // HP回復
	kTrap,
	kWeekPoint,
};

struct MapChipData {
	std::vector<std::vector<MapChipType>> data;
};

class MapChipField {

public:
	~MapChipField();

	struct IndexSet {
		uint32_t xIndex;
		uint32_t yIndex;
	};

	// 範囲矩形
	struct Rect {
		float left;
		float right;
		float top;
		float bottom;
	};

	// 1ブロックのサイズ
	static inline const float kBlockWidth = 1.0f;
	static inline const float kBlockHeight = 1.0f;
	// ブロックの個数
	static inline const uint32_t kNumBlockVirtical = 21;
	static inline const uint32_t kNumBlockHorizontal = 100;

	MapChipData mapChipData_;

	void LoadMapChipCsv(const std::string& filePath);

	MapChipType GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex);
	void DeleteMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex);

	Vector3 GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex);

	uint32_t GetNumBlockVirtical() const;
	uint32_t GetNumBlockHorizontal() const;

	IndexSet GetMapChipIndexSetByPosition(const Vector3& position);

	Rect GetRectByIndex(uint32_t xIndex, uint32_t yIndex);

private:
	void ResetMapChipData();

	// ワールド変換データ
	WorldTransform worldTransform_;
	ViewProjection* viewProjection_ = nullptr;
	// モデル
	Model* model_ = nullptr;
};
