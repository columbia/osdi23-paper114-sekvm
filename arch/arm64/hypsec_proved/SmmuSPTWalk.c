#include "hypsec.h"

/*
 * MmioSPTWalk
 */

void __hyp_text clear_smmu_pt(u32 cbndx, u32 index) 
{
    smmu_pt_clear(cbndx, index);
}

u64 __hyp_text v_walk_smmu_pt(u32 cbndx, u32 index, u64 addr)
{
	u64 ttbr, pgd, pmd, ret;

	ttbr = get_smmu_cfg_hw_ttbr(cbndx, index);
	pgd = walk_smmu_pgd(ttbr, addr, 0U);
	pmd = walk_smmu_pmd(pgd, addr, 0U);
	ret = walk_smmu_pte(pmd, addr);
	return ret;
}

void __hyp_text v_set_smmu_pt(u32 cbndx, u32 index, u64 addr, u64 pte)
{
	u64 ttbr, pgd, pmd;

	ttbr = get_smmu_cfg_hw_ttbr(cbndx, index);
	pgd = walk_smmu_pgd(ttbr, addr, 1U);
	pmd = walk_smmu_pmd(pgd, addr, 1U);
	set_smmu_pte(pmd, addr, pte);
}
