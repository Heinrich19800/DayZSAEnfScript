class Attachments
{
	Container m_Parent;
	EntityAI m_Entity;
	ref AttachmentsWrapper m_AttachmentsContainer;
	ref array<ref SlotsContainer> m_Ics;
	int m_FocusedRow, m_FocusedColumn, m_RowIndex;

	void Attachments( Container parent, EntityAI entity )
	{
		m_Parent = parent;
		m_Entity = entity;
		m_Ics = new array<ref SlotsContainer>();
	}
	
	bool IsEmpty()
	{
		ref array<string> attachments_slots = GetItemSlots( m_Entity );
		int count = attachments_slots.Count();
		return count == 0;
	}
	
	bool IsItemActive()
	{
		ItemBase item = ItemBase.Cast( GetFocusedEntity() );
		if( !item )
		{
			return false;
		}
		return !IsEmpty() && ( !QuantityConversions.HasItemQuantity( item )  || ( QuantityConversions.HasItemQuantity( item ) && !item.CanBeSplit() ) );
	}
	
	bool IsItemWithQuantityActive()
	{
		ItemBase item = ItemBase.Cast( GetFocusedEntity() );
		if( !item )
		{
			return false;
		}
		return !IsEmpty() && QuantityConversions.HasItemQuantity( item ) && item.CanBeSplit();
	}

	void UnfocusAll()
	{
		for ( int i = 0; i < m_Ics.Count(); i++ )
		{
			for ( int j = 0; j < 7; j++ )
			{
				m_Ics.Get( i ).GetMainWidget().FindAnyWidget( "Cursor" + j ).Show( false );
			}
		}
	}

	void SetDefaultFocus()
	{
		m_FocusedRow = 0;
		m_FocusedColumn = 0;
		if( m_Ics.Count() > 0 )
			m_Ics.Get( 0 ).GetMainWidget().FindAnyWidget( "Cursor" + 0 ).Show( true );
		
		EntityAI focused_item = GetFocusedEntity();
		if( focused_item )
		{
			float x, y;
			m_Ics.Get( m_FocusedRow ).GetMainWidget().FindAnyWidget( "Cursor" + m_FocusedColumn ).GetScreenPos( x, y );
			ItemManager.GetInstance().PrepareTooltip( focused_item, x, y );
		}
	}
	
	void SetActive( bool active )
	{
		float alpha;
		if( active )
		{
			SetDefaultFocus();
			alpha = 1;
		}
		else
		{
			alpha = 0;
		}
		m_Parent.GetMainWidget().FindAnyWidget("AttachmentsWrapper").SetAlpha( alpha );
		m_Parent.GetMainWidget().FindAnyWidget("AttachmentsWrapper").Update();
	}
	
	EntityAI GetFocusedEntity()
	{
		if( m_FocusedRow < m_Ics.Count() )
		{
			ItemPreviewWidget ipw = ItemPreviewWidget.Cast( m_Ics.Get( m_FocusedRow ).GetMainWidget().FindAnyWidget( "Render" + m_FocusedColumn ) );
			return ipw.GetItem();
		}
		return null;
	}
	
	int GetFocusedSlot()
	{
		if( m_FocusedRow < m_Ics.Count() )
		{
			ItemPreviewWidget ipw = ItemPreviewWidget.Cast( m_Ics.Get( m_FocusedRow ).GetMainWidget().FindAnyWidget( "Render" + m_FocusedColumn ) );
			return ipw.GetUserID();
		}
		return -1;
	}
	
	void SelectItem()
	{
		if( m_FocusedRow < m_Ics.Count() )
		{
			ItemBase item = ItemBase.Cast( GetFocusedEntity() );
			ItemManager.GetInstance().SetSelectedItem( item, null, m_Ics.Get( m_FocusedRow ).GetMainWidget().FindAnyWidget( "Cursor" + m_FocusedColumn ) );
		}
	}
	
	void Select()
	{
		EntityAI prev_item = EntityAI.Cast( GetFocusedEntity() );
		Man player = GetGame().GetPlayer();
		
		if( ItemManager.GetInstance().IsItemMoving() )
		{
			EntityAI selected_item = ItemManager.GetInstance().GetSelectedItem();
			if( selected_item )
			{
				bool can_add = m_Entity.GetInventory().CanAddAttachment( selected_item );
				if( can_add )
				{
					player.PredictiveTakeEntityToTargetAttachment(m_Entity, selected_item);
					ItemManager.GetInstance().SetSelectedItem( NULL, NULL, NULL );
				}
				else
				{
					Icon selected_icon = ItemManager.GetInstance().GetSelectedIcon();
					if( selected_icon )
					{
						selected_icon.SetActive( false );
					}
					Widget selected_widget = ItemManager.GetInstance().GetSelectedWidget();
					if( selected_widget )
					{
						selected_widget.Show( false );
					}
				}
				
				if( m_Parent.IsInherited( PlayerContainer ) )
				{
					PlayerContainer player_container_parent = PlayerContainer.Cast( m_Parent );
					player_container_parent.UnfocusPlayerAttachmentsContainer();
				}
			}
		}
		else
		{
			if ( prev_item )
			{
				EntityAI item_in_hands = GetGame().GetPlayer().GetHumanInventory().GetEntityInHands();
				InventoryLocation il = new InventoryLocation;
				prev_item.GetInventory().GetCurrentInventoryLocation( il );
				bool reachable = AttachmentsOutOfReach.IsAttachmentReachable( m_Entity, "", il.GetSlot() );
				if( reachable && prev_item.GetInventory().CanRemoveEntity() )
				{
					if( item_in_hands && item_in_hands.GetInventory().CanRemoveEntity() )
					{
						if( GameInventory.CanSwapEntities( item_in_hands, prev_item ) )
						{
							player.PredictiveSwapEntities( item_in_hands, prev_item );
						}
					}
					else
					{
						if( player.GetHumanInventory().CanAddEntityInHands( prev_item ) )
						{
							player.PredictiveTakeEntityToHands( prev_item );
						}
					}
				}
			}		
		}
	}
	
	int GetRecipeCount( bool recipe_anywhere, EntityAI entity1, EntityAI entity2 )
	{
		PluginRecipesManager plugin_recipes_manager = PluginRecipesManager.Cast( GetPlugin( PluginRecipesManager ) );
		return plugin_recipes_manager.GetValidRecipes( ItemBase.Cast( entity1 ), ItemBase.Cast( entity2 ), NULL, PlayerBase.Cast( GetGame().GetPlayer() ) );
	}
	
	bool CanCombine()
	{
		ItemBase ent = ItemBase.Cast( GetFocusedEntity() );
		ItemBase item_in_hands = ItemBase.Cast(	GetGame().GetPlayer().GetHumanInventory().GetEntityInHands() );
		
		return GetRecipeCount( false, ent, item_in_hands ) > 0;
	}
	
	bool CanEquip()
	{
		EntityAI entity = ItemBase.Cast( GetFocusedEntity() );
		InventoryLocation il = new InventoryLocation;
		if( entity.IsInherited( Magazine ) )
		{
			return false;
		}
		bool found = GetGame().GetPlayer().GetInventory().FindFreeLocationFor(entity,FindInventoryLocationType.ATTACHMENT,il);
		if (found)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	
	void EquipItem()
	{
		ItemBase entity = ItemBase.Cast( GetFocusedEntity() );
		if( entity && !entity.IsInherited( Magazine ) )
		{
			if( entity.HasQuantity() )
			{
				entity.OnRightClick();
			}
			else
			{
				GetGame().GetPlayer().PredictiveTakeEntityToInventory( FindInventoryLocationType.ATTACHMENT, entity );
			}
		}
	}
	
	void TransferItem()
	{
		EntityAI entity = GetFocusedEntity();
		if( entity )
		{
			GetGame().GetPlayer().PredictiveTakeEntityToInventory( FindInventoryLocationType.CARGO, entity );
		}
	}
	
	void TransferItemToVicinity()
	{
		EntityAI item = GetFocusedEntity();
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		
		player.PredictiveDropEntity( item );
	}
	
	bool IsActive()
	{
		return m_Parent.GetMainWidget().FindAnyWidget("AttachmentsWrapper").GetAlpha() > 0;
	}

	void MoveGridCursor( int direction )
	{
		ItemManager.GetInstance().HideTooltip();
		UnfocusAll();
		if( direction == Direction.UP )
		{
			m_FocusedRow--;
			if( m_FocusedRow < 0 )
			{
				m_FocusedRow  = m_Ics.Count() - 1;
				Container cnt = Container.Cast( m_Parent.GetParent().GetParent() );
				if( cnt )
					{
						cnt.SetPreviousActive();
					}
					else
					{
						cnt = Container.Cast( m_Parent );
						cnt.SetPreviousActive();
					}
				return;
			}

			int max_row = m_Ics.Get( m_FocusedRow ).GetColumnCount() - 1;
			if( max_row < m_FocusedColumn )
			{
				m_FocusedColumn = max_row;
			}
		}

		if( direction == Direction.DOWN )
		{
			m_FocusedRow++;
			if( m_FocusedRow >= m_Ics.Count() )
			{
				m_FocusedRow = 0 ;
				cnt = Container.Cast( m_Parent.GetParent().GetParent() );
				if( cnt )
				{
					cnt.SetNextActive();
				}
				else
				{
					cnt = Container.Cast( m_Parent );
					cnt.SetNextActive();
				}
				return;
			}

			max_row = m_Ics.Get( m_FocusedRow ).GetColumnCount() - 1;
			if( max_row < m_FocusedColumn )
			{
				m_FocusedColumn = max_row;
			}
		}

		if( direction == Direction.RIGHT )
		{
			if( m_Ics.Count() > 0 )
			{
				m_FocusedColumn++;
				if( m_FocusedColumn == m_Ics.Get( m_FocusedRow ).GetColumnCount() )
				{
					m_FocusedColumn = 0;
				}
			}
			else
				return;
		}

		if( direction == Direction.LEFT )
		{
			if( m_Ics.Count() > 0 )
			{
				m_FocusedColumn--;
				if( m_FocusedColumn < 0 )
				{
					m_FocusedColumn = m_Ics.Get( m_FocusedRow ).GetColumnCount() - 1;
				}
			}
			else
				return;
		}

		m_Ics.Get( m_FocusedRow ).GetMainWidget().FindAnyWidget( "Cursor" + m_FocusedColumn ).Show( true );
		
		EntityAI focused_item = GetFocusedEntity();
		if( focused_item )
		{
			float x, y;
			m_Ics.Get( m_FocusedRow ).GetMainWidget().FindAnyWidget( "Cursor" + m_FocusedColumn ).GetScreenPos( x, y );
			ItemManager.GetInstance().PrepareTooltip( focused_item, x, y );
		}
	}

	void Remove()
	{
		for( int i = 0; i < m_Ics.Count(); i++ )
		{
			m_Parent.Remove( m_Ics.Get( i ) );
			delete m_Ics.Get( i ).GetMainWidget();
		}
		m_Ics.Clear();

		m_Parent.Refresh();
	}
	
	int GetAttachmentHeight()
	{
		return m_AttachmentsContainer.Count();
	}

	void RefreshAtt()
	{
		if( !m_Entity )
		{
			return;
		}

		ref array<string> attachments_slots = GetItemSlots( m_Entity );
		array<string> slots = attachments_slots;
		int count =  attachments_slots.Count();

		Att( count, slots );
	}

	void Att( int count, array<string> slots )
	{
		Widget ghost_widget;
		int slot_id;

		for ( int i = 0; i < count; i++ )
		{
			bool draggable = true;
			string slot_name = slots.Get( i );
			
			while( !m_Entity.CanDisplayAttachmentSlot( slot_name ) )
			{
				i++;
				if( slots.Count() > i )
					slot_name = slots.Get( i );
				else
					return;
			}
			
			string path = "CfgSlots" + " Slot_" + slot_name;
			string icon_name2;
			GetGame().ConfigGetText( path + " ghostIcon", icon_name2 );
			//icon_name2 = "missing";
			
			ImageWidget ghost_icon;
			if ( ghost_icon )
			{
				ghost_icon.LoadImageFile( 0, "set:dayz_inventory image:" + icon_name2 );
			}

			GetGame().ConfigGetText( path + " name", slot_name );
			slot_id = InventorySlots.GetSlotIdFromString( slot_name );

			ItemPreviewWidget item_preview2 = ItemPreviewWidget.Cast( m_Parent.Get( ( i / 7 ) + m_RowIndex ).GetMainWidget().FindAnyWidget( "Icon" + i % 7 ).FindAnyWidget( "Render" + i % 7 ) );
			ImageWidget image_widget2 = ImageWidget.Cast( item_preview2.GetParent().GetParent().FindAnyWidget( "GhostSlot" + i % 7 ) );
			if( image_widget2 && m_Entity.GetInventory().FindAttachment( slot_id ) == NULL )
			{
				image_widget2.Show( true );
			}
			else
			{
				image_widget2.Show( false );
			}

			item_preview2.GetParent().Show( true );

			if( icon_name2 != "" )
				image_widget2.LoadImageFile( 0, "set:dayz_inventory image:" + icon_name2 );
			item_preview2.SetItem( m_Entity.GetInventory().FindAttachment( slot_id ) );
			item_preview2.SetModelOrientation( Vector( 0, 0, 0 ) );
			item_preview2.SetView( m_Entity.GetViewIndex() );
			
			int size_x, size_y;
			GetGame().GetInventoryItemSize( InventoryItem.Cast(m_Entity.GetInventory().FindAttachment( slot_id )) , size_x, size_y );
			int capacity = size_x * size_y;
			TextWidget tw = TextWidget.Cast( item_preview2.GetParent().GetParent().FindAnyWidget( "ItemSize" + i % 7 ) );
			
			#ifdef PLATFORM_CONSOLE
			tw.Show( true );
			#endif
			if(capacity == 0)
			{
				tw.SetText( "" );
			}
			else
			{
				tw.SetText( capacity.ToString() );
			}

			if( !ItemManager.GetInstance().IsDragging() )
			{
				ItemManager.GetInstance().SetTemperature( m_Entity.GetInventory().FindAttachment( slot_id ), item_preview2 );
			}

			Widget item_w = item_preview2;
			EntityAI item = m_Entity.GetInventory().FindAttachment( slot_id );
			if( item == NULL )
			{
				item_w.FindAnyWidget( "QuantityPanel" + i % 7 ).Show( false );
				item_w.GetParent().FindAnyWidget( "OutOfReach" + i % 7 ).Show( false );
			}

			item_w.FindAnyWidget( "Mounted" + i % 7 ).Show( false );

			if ( item_w && item )
			{
				if( m_Entity.GetInventory().GetSlotLock( slot_id ) && ItemManager.GetInstance().GetDraggedItem() != item )
				{
					item_w.FindAnyWidget( "Mounted" + i % 7 ).Show( true );
					draggable = false;
				}

				int has_quantity	= QuantityConversions.HasItemQuantity( item );
				int stack_max		= InventorySlots.GetStackMaxForSlotId( slot_id );
				Widget quantity_panel = item_w.FindAnyWidget( "QuantityPanel" + i % 7 );
				TextWidget item_quantity = TextWidget.Cast( item_w.FindAnyWidget( "Quantity" + i % 7 ) );
				ProgressBarWidget quantity_progress = ProgressBarWidget.Cast( item_w.FindAnyWidget( "QuantityBar" + i % 7 ) );
				Widget quantity_stack = item_w.FindAnyWidget( "QuantityStackPanel" + i % 7 );
				if ( has_quantity == QUANTITY_HIDDEN )
				{
					quantity_panel.Show( false );
				}
				else
				{
					quantity_panel.Show( true );
					if ( has_quantity == QUANTITY_COUNT || stack_max > 1 )
					{
						item_quantity.SetText( QuantityConversions.GetItemQuantityText( item ) );
						quantity_stack.Show( true );
						quantity_progress.Show( false );
					}
					else if ( has_quantity == QUANTITY_PROGRESS )
					{
						float progress_max = quantity_progress.GetMax();
						int max = item.ConfigGetInt( "varQuantityMax" );
						int count2 = item.ConfigGetInt( "count" );
						float quantity = QuantityConversions.GetItemQuantity( InventoryItem.Cast( item ) );
						if ( count2 > 0 )
						{
							max = count2;
						}
						if ( max > 0 )
						{

							float value = Math.Round( ( quantity / max ) * 100 );
							quantity_progress.SetCurrent( value );
						}
						quantity_stack.Show( false );
						quantity_progress.Show( true );
					}
				}
			}

			if( item )
			{
				ImageWidget image_widget3 = ImageWidget.Cast( item_preview2.GetParent().FindAnyWidget( "OutOfReach" + i % 7 ) );
				PlayerBase p = PlayerBase.Cast( GetGame().GetPlayer() );
				bool in_hands_condition		= m_Entity.GetHierarchyRoot() && item.GetInventory().CanRemoveEntity();
				bool in_vicinity_condition	= !m_Entity.GetHierarchyRoot() && AttachmentsOutOfReach.IsAttachmentReachable( m_Entity, slot_name );
				if( in_hands_condition || in_vicinity_condition )
				{
					image_widget3.Show( false );
				}
				else
				{
					image_widget3.Show( true );
					draggable = false;
				}
			}
					
			if( draggable )
			{
				item_preview2.GetParent().SetFlags( WidgetFlags.DRAGGABLE );
			}
			else
			{
				item_preview2.GetParent().ClearFlags( WidgetFlags.DRAGGABLE );
			}
		}
	}

	void InitAttachmentGrid( int att_row_index )
	{
		m_RowIndex = att_row_index;
		ref array<string> attachments_slots = GetItemSlots( m_Entity );

		array<string> slots = attachments_slots;
		int count = attachments_slots.Count();

		int number_of_rows = ( count / 7 );
		if( count % 7 == 0 )
		{
			number_of_rows--;
		}
		m_AttachmentsContainer = new AttachmentsWrapper( m_Parent );
		m_AttachmentsContainer.GetRootWidget().SetSort( att_row_index );
		for ( int i = 0; i < number_of_rows + 1; i++ )
		{
			SlotsContainer ic = new SlotsContainer( m_AttachmentsContainer );
			m_AttachmentsContainer.Insert( ic );

			if( i == number_of_rows && count % 7 != 0 )
			{
				ic.SetColumnCount( count % 7 );
			}
			else
			{
				ic.SetColumnCount( 7 );
			}

			m_Ics.Insert( ic );
			m_Parent.Insert( ic );
			for( int j = 0; j < 7; j++ )
			{
				WidgetEventHandler.GetInstance().RegisterOnDropReceived( ic.GetMainWidget().FindAnyWidget( "Icon" + j ), m_Parent, "OnDropReceivedFromHeader2" );
				WidgetEventHandler.GetInstance().RegisterOnDropReceived( ic.GetMainWidget().FindAnyWidget( "GhostSlot" + j ), m_Parent, "OnDropReceivedFromHeader2" );
				WidgetEventHandler.GetInstance().RegisterOnDropReceived( ic.GetMainWidget().FindAnyWidget( "PanelWidget" + j ), m_Parent, "OnDropReceivedFromHeader2" );

				WidgetEventHandler.GetInstance().RegisterOnDraggingOver( ic.GetMainWidget().FindAnyWidget( "Icon" + j ),  m_Parent, "DraggingOverHeader2" );
				WidgetEventHandler.GetInstance().RegisterOnDraggingOver( ic.GetMainWidget().FindAnyWidget( "GhostSlot" + j ), m_Parent, "DraggingOverHeader2" );
				WidgetEventHandler.GetInstance().RegisterOnDraggingOver( ic.GetMainWidget().FindAnyWidget( "PanelWidget" + j ), m_Parent, "DraggingOverHeader2" );
				
				WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown( ic.GetMainWidget().FindAnyWidget( "Icon" + j ), m_Parent, "MouseClick2" );
				WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown( ic.GetMainWidget().FindAnyWidget( "GhostSlot" + j ), m_Parent, "MouseClick2" );
				WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown( ic.GetMainWidget().FindAnyWidget( "PanelWidget" + j ), m_Parent, "MouseClick2" );
			}
		}

		Att( count, slots );

		for ( i = 0; i < count; i++ )
		{
			ItemPreviewWidget item_preview2 = ItemPreviewWidget.Cast( m_Parent.Get( ( i / 7 ) + 1 ).GetMainWidget().FindAnyWidget( "Icon" + i % 7 ).FindAnyWidget( "Render" + i % 7 ) );
			WidgetEventHandler.GetInstance().RegisterOnDrag( item_preview2.GetParent(), m_Parent, "OnIconDrag" );
			WidgetEventHandler.GetInstance().RegisterOnDrop( item_preview2.GetParent(), m_Parent, "OnIconDrop" );
			WidgetEventHandler.GetInstance().RegisterOnDoubleClick( item_preview2.GetParent(), m_Parent, "DoubleClick" );
		}
	}

	array<string> GetItemSlots( EntityAI e )
	{
		TStringArray searching_in = new TStringArray;
		searching_in.Insert( CFG_VEHICLESPATH );
		searching_in.Insert( CFG_WEAPONSPATH );
		searching_in.Insert( CFG_MAGAZINESPATH );

		array<string> attachments_slots	= new array<string>;

		for ( int s = 0; s < searching_in.Count(); ++s )
		{
			string cfg_name = searching_in.Get( s );
			string path = cfg_name + " " + e.GetType();

			if ( GetGame().ConfigIsExisting( path ) )
			{
				g_Game.ConfigGetTextArray( path + " attachments", attachments_slots );
				if ( e.IsWeapon() && (!e.ConfigIsExisting("DisplayMagazine") || e.ConfigGetBool("DisplayMagazine")) )
				{
					attachments_slots.Insert( "magazine" );
				}
				return attachments_slots;
			}
		}
		if ( e.IsWeapon() && (!e.ConfigIsExisting("DisplayMagazine") || e.ConfigGetBool("DisplayMagazine")) )
		{
			attachments_slots.Insert( "magazine" );
		}
		return attachments_slots;
	}
}
