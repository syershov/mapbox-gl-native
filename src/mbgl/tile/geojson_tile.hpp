#pragma once

#include <mbgl/tile/geometry_tile.hpp>
#include <mbgl/util/feature.hpp>

namespace mbgl {
namespace style {
class GeoJSONData;
} // style

class TileParameters;

class GeoJSONTile : public GeometryTile {
public:
    GeoJSONTile(const OverscaledTileID&,
                std::string sourceID,
                const TileParameters&,
                std::shared_ptr<style::GeoJSONData>);

    void updateData(std::shared_ptr<style::GeoJSONData> data, CanonicalTileID tileId, bool resetLayers = false);

    void querySourceFeatures(
        std::vector<Feature>& result,
        const SourceQueryOptions&) override;
};

} // namespace mbgl
