class EN5C_Edible_Base extends ItemBase
{
	autoptr FoodStage m_FoodStage;
	
	void EN5C_Edible_Base()
	{
		if ( !m_FoodStage )
		{
			m_FoodStage = new FoodStage ( this );
		}
	}
	
	void Initialize()
	{
		FoodManager.RefreshVisual ( this );
	}
	
	//on store save/load
	void OnStoreSave( ParamsWriteContext ctx )
	{   
		super.OnStoreSave(ctx);
		
		//Food stage name 
		autoptr Param1<string> stage_name = new Param1<string>( GetFoodStage().GetName() );
		ctx.Write( stage_name.param1 );
		
		//Selection index
		autoptr Param1<int> selection_idx = new Param1<int>( GetFoodStage().GetSelectionIndex() );
		ctx.Write( selection_idx.param1 );
		
		//Texture index
		autoptr Param1<int> texture_idx = new Param1<int>( GetFoodStage().GetTextureIndex() );
		ctx.Write( texture_idx.param1 );
		
		//Material index
		autoptr Param1<int> material_idx = new Param1<int>( GetFoodStage().GetMaterialIndex() );
		ctx.Write( material_idx.param1 );
		
		//Food properties
		//size
		autoptr Param1<int> food_prop_size;
		if ( GetFoodStage().GetFoodProperties() )	//if not null
		{
			food_prop_size = new Param1<int>( GetFoodStage().GetFoodProperties().Count() );
		}
		else
		{
			food_prop_size = new Param1<int>( 0 );
		}
		ctx.Write( food_prop_size.param1 );
		//data
		for ( int i = 0; i < food_prop_size.param1; i++ )
		{
			autoptr Param1<float> food_prop = new Param1<float>( GetFoodStage().GetFoodProperties().Get( i ) );
			ctx.Write( food_prop.param1 );
		}
		
		//Modifiers
		//size
		autoptr Param1<int> modifiers_size;
		if ( GetFoodStage().GetModifiers() )	//if not null
		{
			modifiers_size = new Param1<int>( GetFoodStage().GetModifiers().Count() );
		}
		else
		{
			modifiers_size = new Param1<int>( 0 );
		}
		ctx.Write( modifiers_size.param1 );
		//data
		for ( int j = 0; j < modifiers_size.param1; j++ )
		{
			autoptr Param1<string> modifier = new Param1<string>( GetFoodStage().GetModifiers().Get( j ) );
			ctx.Write( modifier.param1 );
		}
		
		//Rotten state
		autoptr Param1<bool> is_rotten = new Param1<bool>( GetFoodStage().IsRotten() );
		ctx.Write( is_rotten.param1 );
	}

	void OnStoreLoad( ParamsReadContext ctx )
	{
		super.OnStoreLoad(ctx);
		
		//Food stage name 
		autoptr Param1<string> stage_name = new Param1<string>( "" );
		ctx.Read( stage_name );
		GetFoodStage().SetName( stage_name.param1 );
		
		//Selection index
		autoptr Param1<int> selection_idx = new Param1<int>( 0 );
		ctx.Read( selection_idx );
		GetFoodStage().SetSelectionIndex( selection_idx.param1 );
		
		//Texture index
		autoptr Param1<int> texture_idx = new Param1<int>( 0 );
		ctx.Read( texture_idx );
		GetFoodStage().SetTextureIndex( texture_idx.param1 );
		
		//Material index
		autoptr Param1<int> material_idx = new Param1<int>( 0 );
		ctx.Read( material_idx );
		GetFoodStage().SetMaterialIndex( material_idx.param1 );
		
		//Food properties
		//count
		autoptr Param1<int> food_prop_size = new Param1<int>( 0 );
		ctx.Read( food_prop_size );		
		//data
		for ( int i = 0; i < food_prop_size.param1; i++ )
		{
			autoptr Param1<float> food_prop = new Param1<float>( 0 );
			ctx.Read( food_prop );
			GetFoodStage().GetFoodProperties().Insert( food_prop.param1 );
		}
		
		//Modifiers
		//count
		autoptr Param1<int> modifiers_size = new Param1<int>( 0 );
		ctx.Read( modifiers_size );		
		//data
		for ( int j = 0; j < modifiers_size.param1; j++ )
		{
			autoptr Param1<string> modifier = new Param1<string>( "" );
			ctx.Read( modifier );
			GetFoodStage().GetModifiers().Insert( modifier.param1 );
		}
		
		//Rotten state
		autoptr Param1<bool> is_rotten = new Param1<bool>( false );
		ctx.Read( is_rotten );
		GetFoodStage().SetRottenState( is_rotten.param1 );		
		
		//refresh visual after load
		FoodManager.RefreshVisual ( this );
	}
	
	FoodStage GetFoodStage()
	{
		return this.m_FoodStage;
	}
	
	//food types
	bool IsMeat()
	{
		return false;
	}
}

//Global function
//TODO - remove when INIT event in fixed
void FoodInitialize( ItemBase item )
{
	EN5C_Edible_Base food = ( EN5C_Edible_Base ) item;
	food.Initialize();
}
